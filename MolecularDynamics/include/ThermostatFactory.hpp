#ifndef __THERMOSTATFACTORY_HPP__
#define __THERMOSTATFACTORY_HPP__
#include <memory>

template<int D>
class MDSimulation;

enum ThermostatType { ANDERSON };

template<int D>
class Thermostat {

	public:
		virtual void setT(const double temp) = 0;
		virtual double getT() const = 0;
		virtual void execute() = 0;
		virtual void setNu(const double nu) {};
		virtual double getNu() const {};
};


template<int D>
class ThermostatFactory {
	public:
		virtual Thermostat<D>* createAndersonThermostat(MDSimulation<D>* sim_, double temp_, double nu_) = 0;
};

#endif
