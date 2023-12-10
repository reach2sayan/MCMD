#include <iostream>
#include "MDSimulation.hpp"

extern constexpr int HISTOGRAM_RESOLUTION = 201;
template<int D>
MDSimulation<D>::MDSimulation(int dim_, double dt_, ForceFunc f, PotentialFunc p, double r_inter_, double r_verlet_, int verletUpdate_) : 
	particles(std::make_unique<MDParticleList<D>>()),
	pause(false),
	graphDataFirst(0),
	graphDataLast(0),
	thermo{std::make_unique<AndersonThermostat<D>>(this, 0, 10)},
	pot(p),
	force(f),
	dt(dt_),
	t(0),
	r_inter(r_inter_),
	r_verlet(r_verlet_),
	simBox(Vector::Zero()),
	radial(VectorHistogram::Zero(HISTOGRAM_RESOLUTION)),
	directional(MatrixHistogram::Zero(HISTOGRAM_RESOLUTION,HISTOGRAM_RESOLUTION)),
	verletSteps(0),
	verletUpdate(verletUpdate_),
	dim(dim_),
	histogramResolution(HISTOGRAM_RESOLUTION),
	periodic(false)
{}

template<int D>
void MDSimulation<D>::initSimulation(bool periodic_, const Vector simBox_, InitPositionFunc r0_, InitVelocityFunc v0_, int histogramResolution_, double histogramLength_){

	histogramResolution = histogramResolution_ == 0 ? histogramResolution_ : HISTOGRAM_RESOLUTION;
	histogramLength = histogramLength_;
	simBox = simBox_;
	if (r0_){
		int i = 0;
		for(auto& particle : *particles)
			particle->r = r0_(i++);
	}
	else{
		double n = ceil(pow(static_cast<double>(particles->size()), 1./dim));
		auto particle = particles->begin();
		switch(dim){
			case 2:
				for (int i = 0; i < n; i++)
					for(int j = 0; j < n; j++)
						if(particle < particles->end()){
							(*particle)->r[0] = static_cast<double>(i * simBox[0]/n);
							if (j & 1)
								(*particle)->r[0] += 1.0/(2.0*n);
							(*particle)->r[1] = static_cast<double>(j * simBox[1]/n);
							particle++;
						}
				break;
			case 3:
				for (int i = 0; i < n; i++){
					for(int j = 0; j < n; j++){
						for(int k = 0; k < n; k++){
							if(particle != particles->end()){
								(*particle)->r[0] = static_cast<double>(i * simBox[0] / n);
								(*particle)->r[1] = static_cast<double>(j * simBox[1] / n);
								(*particle)->r[2] = static_cast<double>(k * simBox[2] / n);
								particle++;
							}
						}
					}
				}
				break;
		}
	}
	if (v0_){
		int i = 0;
		for(auto& particle: *particles)
			particle->v = v0_(i++);
	}
	else{
		for(auto& particle: *particles)
			particle->v = Vector::Zero();
	}
	
	periodic = periodic_;
	t = 0;
	radial = VectorHistogram::Zero(HISTOGRAM_RESOLUTION);
	directional = MatrixHistogram::Zero(HISTOGRAM_RESOLUTION, HISTOGRAM_RESOLUTION);
	ePot = ePotMin = refreshVerletLists(true, true);
	eKin = 0;
	for (const auto& particle : *particles){
		eKin += particle->v.squaredNorm();
	}

	eKin *= 0.5;
	resetGraphs();
	updateGraphs();
	pause = true;
}

template<int D>
inline void MDSimulation<D>::ApplyPeriodicBoundaryCondition(MDParticle<D>* particle){
	for (int i = 0; i < dim; i++)
		particle->r[i] -= simBox[i] * floor(particle->r[i] / simBox[i]);
}

template<int D>
void MDSimulation<D>::velocityVerletStep(bool countRadial){
	if (!pause) {
		for (auto& particle : *particles){
			particle->v += 0.5*dt*particle->a;
			particle->r += dt*particle->v;

			if(periodic)
				ApplyPeriodicBoundaryCondition(particle);
		}

		if(verletSteps > verletUpdate){
			ePot = refreshVerletLists(true, countRadial);
			verletSteps = 0;
		}
		else
			ePot = velocityVerletForce(); // new force with new r
		
		verletSteps++;
		for(auto& particle : *particles)
			particle->v += 0.5*dt*particle->a;

		eKin = 0;
		for(auto& particle: *particles)
			eKin += particle->v.squaredNorm();
		eKin *= 0.5;
		t += dt;
	}
}

// has to be called after the velocityVerletStep function to extend the graphs by the last time step
template<int D>
void MDSimulation<D>::updateGraphs(){
	if (pause)
		return;

	graphDataLast = (graphDataLast->next = new graphData_t);
	// The first list entry (graphDataFirst) contains the maximum values of the graphs (for normalization).
	// Assignment of new values and query for wether they are greater than last maximum can be combined:
	
	graphDataLast->ePot = ePot;
	if (ePot > graphDataFirst->ePot) 
		graphDataFirst->ePot = graphDataLast->ePot;

	graphDataLast->eKin = eKin;
	if (eKin > graphDataFirst->eKin) 
		graphDataFirst->eKin = graphDataLast->eKin;

	graphDataLast->next = nullptr;
	if (ePot < ePotMin)
		ePotMin = ePot;
}

template<int D>
void MDSimulation<D>::resetGraphs(){

	graphData_t* graphData = graphDataFirst;
	if (graphData){
		graphData->ePot = graphData->eKin = 0;
		graphData = graphData->next;
		while (graphData){
			graphData_t* temp = graphData;
			graphData = graphData->next;
			delete temp;
		}
		graphDataLast = graphDataFirst;
	}
	else{
		graphDataFirst = graphDataLast = new graphData_t;
		graphDataFirst->eKin = graphDataFirst->ePot = 0;
		graphDataFirst->next = nullptr;
	}
}

template<int D>
typename MDSimulation<D>::MatrixHistogram MDSimulation<D>::getDirectionalDistribution() const {
	float max = directional.maxCoeff();
	return directional/max;
}

template<int D>
double MDSimulation<D>::refreshVerletLists(bool calc, bool countRadial){
	double r_abs, pot_ = 0;
	Vector r_, f_;
	if (calc)
		for(auto& particle : *particles)
			particle->a = Vector::Zero();

	for(auto entry = particles->begin(); entry != particles->end(); entry++){
		(*entry)->verletList->clear();
		for(auto verlet = entry+1 ; verlet < particles->end(); verlet++){
			r_ = (*entry)->r - (*verlet)->r;
			if(periodic)
				for(int i = 0; i < dim; i++)
					if (abs(r_[i]) > 0.5 * simBox[i])
						r_[i] -= copysign(simBox[i],r_[i]);
			r_abs = r_.norm();

			if(countRadial){

				double hr = histogramResolution;
				double hl = histogramLength;

				if(r_abs < hl)
					radial[static_cast<Eigen::Index>(r_abs/hl * hr) + 1]++;
				if(dim == 2){
					if (abs(r_[0]) < hl && abs(r_[1]) < hl){
						directional(static_cast<Eigen::Index>((r_[0] / (2. * hl) + 0.5)*hr), static_cast<Eigen::Index>((r_[1] / (2*hl) + 0.5) * hr))++;
						directional(static_cast<Eigen::Index>((r_[0] / (-2. * hl) + 0.5)*hr), static_cast<Eigen::Index>((r_[1]/(-2. * hl) + 0.5)*hr))++;
					}
				}
			}

			if(r_verlet > 0 && r_abs > r_verlet)
				continue;

			(*entry)->verletList->push_back(*verlet);
			if(calc && (r_abs < r_inter || r_inter == 0)){
				f_ = force(r_);
				pot_ += pot(r_);
				(*entry)->a += f_;
				(*verlet)->a -= f_;
			}
		}
	}
	return pot_;
}

template<int D>
double MDSimulation<D>::velocityVerletForce(){

	double pot_ = 0;
	double r_inter_2 = r_inter*r_inter;
	Vector f_, r_;

	for (auto& particle : *particles)
		particle->a = Vector::Zero();

	// address every pair of particles only once:
	
	for(auto& particle : *particles){
		for(auto& verlet : *(particle->verletList)){
			r_ = particle->r - verlet->r;
			if(periodic){
				for(int i = 0; i < dim; i++){
					if (abs(r_[i]) > 0.5*simBox[i])
						r_[i] -= std::copysign(simBox[i],r_[i]);
				}
			}
			if (r_inter_2 > 0 && (r_.squaredNorm() > r_inter_2))
				continue;

			f_ = force(r_);
			pot_ += pot(r_);
			particle->a += f_;
			verlet->a -= f_;
		}
	}
	return pot_;
}

template class MDSimulation<2>;
