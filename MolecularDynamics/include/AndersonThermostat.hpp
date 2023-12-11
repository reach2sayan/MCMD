#ifndef __ANDERSONTHERMOSTAT_HPP__
#define __ANDERSONTHERMOSTAT_HPP__

#include "ThermostatFactory.hpp"

template<int D>
class AndersonThermostat : public Thermostat<D> {

public:
	AndersonThermostat(MDSimulation<D>* sim, double temp, double nu);

	void setT(const double temp) override ;
	double getT() const override;
	void setNu(const double nu) override;
	double getNu() const override;
  void execute();
	~AndersonThermostat() = default;

private:
	MDSimulation<D>* sim;
	double temp;
	double nu;
	double p;
};

template<int D>
class AndersonThermostatFactory : public ThermostatFactory<D> {
	
	public:
		Thermostat<D>* createAndersonThermostat(MDSimulation<D>* sim_, double temp_, double nu_) override {
			return new AndersonThermostat<D>(sim_, temp_, nu_);
		}
};

#endif
