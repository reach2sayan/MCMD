#ifndef __THERMOSTATFACTORY_HPP__
#define __THERMOSTATFACTORY_HPP__
#include <memory>

class MDSimulation;

enum ThermostatType { ANDERSON };

class Thermostat {

	public:
		virtual void setT(const double temp) = 0;
		virtual double getT() const = 0;
		virtual void execute() = 0;
		virtual void setNu([[maybe_unused]] const double nu) {};
		virtual double getNu() const { return 0;};
};

class ThermostatFactory {
	public:
		virtual Thermostat* createAndersonThermostat(MDSimulation* sim_, double temp_, double nu_) = 0;
};

#endif
