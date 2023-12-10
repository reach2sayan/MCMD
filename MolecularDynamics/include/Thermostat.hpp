#ifndef __THERMOSTAT_HPP__
#define __THERMOSTAT_HPP__

template<int D>
class MDSimulation;

template<int D>
class Thermostat {

	public:
		Thermostat() = delete;
		Thermostat(MDSimulation<D>* sim_, double temp_) : sim{sim_}, temp{temp_} {}
		virtual ~Thermostat() = default;
		
		virtual void setT(const double temp) { this->temp = temp;}
		virtual double getT() const { return temp; }
		virtual void execute() = 0;

	protected:
		MDSimulation<D>* sim;
		double temp;
};


#endif
