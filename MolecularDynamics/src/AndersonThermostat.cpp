#include "AndersonThermostat.hpp"
#include "ThermostatFactory.hpp"
#include "MDSimulation.hpp"

using namespace MDConstants;

void AndersonThermostat::execute(){

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

inline AndersonThermostat::AndersonThermostat(MDSimulation* sim_, double temp_, double nu_) :
	sim(sim_),temp(temp_), nu(-1.0*nu_) {
		p = 1 - exp(-1*nu_*sim_->getDt());
	}

inline void AndersonThermostat::setNu(const double nu_){
	nu = (-1.0)*nu_;
	p = 1 - exp(-1*nu_*(this->sim->getDt()));
}

inline double AndersonThermostat::getNu() const {
	return (-1.0)*nu;
}

inline void AndersonThermostat::setT(const double temp_) { 
	this->temp = -2.0*temp_;
}

inline double AndersonThermostat::getT() const {
	return -0.5*this->temp;
}

inline Thermostat* AndersonThermostatFactory::createAndersonThermostat(MDSimulation* sim_, double temp_, double nu_) {
	return new AndersonThermostat(sim_, temp_, nu_);
}
