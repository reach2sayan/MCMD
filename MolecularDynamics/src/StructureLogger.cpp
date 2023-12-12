#include "Logger.hpp"
#include "MDSimulation.hpp"

StructureLogger::StructureLogger(MDSimulation& sim_) : sim(sim_) {
	sim_.registerLogger(this);
}

void StructureLogger::log() const {
}
