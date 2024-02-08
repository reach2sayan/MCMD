#ifndef __ANDERSONTHERMOSTAT_HPP__
#define __ANDERSONTHERMOSTAT_HPP__

#include "ThermostatFactory.hpp"

class AndersonThermostat : public Thermostat {
 public:
  AndersonThermostat(MDSimulation* sim, double temp, double nu);

  void setT(const double temp) override;
  double getT() const override;
  void setNu(const double nu) override;
  double getNu() const override;
  void execute() override;
  ~AndersonThermostat() = default;

 private:
  MDSimulation* sim;
  double temp;
  double nu;
  double p;
};

class AndersonThermostatFactory : public ThermostatFactory {
 public:
  Thermostat* createThermostat(MDSimulation* sim_, double temp_,
			       double nu_) override;
};

#endif
