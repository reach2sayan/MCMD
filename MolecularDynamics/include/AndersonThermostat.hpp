#ifndef __ANDERSONTHERMOSTAT_HPP__
#define __ANDERSONTHERMOSTAT_HPP__

template<int D>
class MDSimulation;

template<int D>
class AndersonThermostat{

public:
	AndersonThermostat(MDSimulation<D>* sim, double temp, double nu);

	void setT(const double temp);
	double getT() const;
	void setNu(const double nu);
	double getNu() const;
  void execute();

private:
	MDSimulation<D>* sim;
	double temp, nu;
	double p;
};
#endif
