#include "Logger.hpp"
#include "MDSimulation.hpp"

StructureLogger::StructureLogger(MDSimulation* sim_, std::string&& filename_) : sim(sim_) {
	sim_->registerLogger(this);
	myfile.open(filename_);
}

StructureLogger::~StructureLogger(){
	sim->unregisterLogger(this);
	myfile.close();
}

void StructureLogger::log() const {
	
	int i = 0;
	std::cout << sim->GetSimulationBox() << std::endl;;
	for(auto& particle : *(sim->particles))
		std::cout << i << " " << particle->r.transpose() << std::endl;
	std::cout << " <<<<<<<<<<<<<<<<<<<<<<<<<<< " << std::endl;

}
