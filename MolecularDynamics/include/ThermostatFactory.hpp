#ifndef __THERMOSTATFACTORY_HPP__
#define __THERMOSTATFACTORY_HPP__
#include <memory>

template<int D>
class MDSimulation;

enum ThermostatType { ANDERSON };

template<int D>
class Thermostat {

	public:
		Thermostat(MDSimulation<D>* sim_, double temp_) : sim(sim_), temp(temp_) {}
		virtual void setT(const double temp) { this->temp = temp;}
		virtual double getT() const { return temp; }
		virtual void execute() = 0;

	protected:
		MDSimulation<D>* sim;
		double temp;
};


template<int D>
class ThermostatFactory {
	public:
		virtual Thermostat<D>* createAndersonThermostat(MDSimulation<D>* sim_, double temp_, double nu_) = 0;
};

#endif
