#ifndef __ANDERSONTHERMOSTAT_HPP__
#define __ANDERSONTHERMOSTAT_HPP__

#include "Thermostat.hpp"

template<int D>
class AndersonThermostat : public Thermostat<D> {

public:
	AndersonThermostat(MDSimulation<D>* sim, double temp, double nu);

	void setT(const double temp) override;
	double getT() const override;
	void setNu(const double nu);
	double getNu() const;
  void execute();

private:
	double nu;
	double p;
};
#endif
