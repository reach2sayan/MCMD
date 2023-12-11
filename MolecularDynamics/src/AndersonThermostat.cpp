#include "AndersonThermostat.hpp"
#include "ThermostatFactory.hpp"
#include "MDSimulation.hpp"
#include "utility.hpp"

using namespace MDConstants;

template<int D>
void AndersonThermostat<D>::execute(){

	if (this->sim->pause)
		return;

	for (auto& particle : *(this->sim->particles)){

		if (mersenneTwister() < p){
			double u1 = log(1.0 - mersenneTwister());
			double u2 = TWOPI * mersenneTwister();
			int dim = this->sim->getDim();
			double s = sin(u2), c = cos(u2);

			switch(dim){
				case 2:
					particle->v[0] = std::sqrt(this->temp*u1)*c;
					particle->v[1] = std::sqrt(this->temp*u1)*s;
					break;
				case 3:
					double u3 = M_PI * mersenneTwister();
					double s_ = std::sin(u3), c_ = std::cos(u3);
					particle->v[0] = std::sqrt(this->temp*u1)*s_*c;
					particle->v[1] = std::sqrt(this->temp*u1)*s_*s;
					particle->v[2] = std::sqrt(this->temp*u1)*c_;
					break;
			}
		}
	}
}

template<int D>
inline AndersonThermostat<D>::AndersonThermostat(MDSimulation<D>* sim_, double temp_, double nu_) :
	Thermostat<D>{sim_,temp_}, nu{-1.0*nu_} {
		p = 1 - exp(-1*nu_*sim_->getDt());
	}

template<int D>
inline void AndersonThermostat<D>::setNu(const double nu_){
	nu = (-1.0)*nu_;
	p = 1 - exp(-1*nu_*(this->sim->getDt()));
}

template<int D>
inline double AndersonThermostat<D>::getNu() const {
	return (-1.0)*nu;
}

template<int D>
inline void AndersonThermostat<D>::setT(const double temp_) { 
	this->temp = -2.0*temp_;
}

template<int D>
inline double AndersonThermostat<D>::getT() const {
	return -0.5*this->temp;
}
template class AndersonThermostat<2>;
