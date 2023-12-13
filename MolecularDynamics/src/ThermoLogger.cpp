#include "Logger.hpp"
#include "MDSimulation.hpp"

ThermoLogger::ThermoLogger(MDSimulation* sim_, std::string&& filename_) : sim(sim_) {
	sim_->registerLogger(this);
	myfile.open(filename_);
}

ThermoLogger::~ThermoLogger(){
	sim->unregisterLogger(this);
	myfile.close();
}

void ThermoLogger::log() const {

	static int i = 0;
	std::cout << i << " " << sim->getEKin() << " " << sim->getEPot()  << std::endl;
	i++;

}
