#include "CalculatorFactory.hpp"
#include "Logger.hpp"
#include "MDSimulation.hpp"
#include "ThermostatFactory.hpp"
#include "AndersonThermostat.hpp"
#include "glutSetup2d.hpp"
#include <eigen3/Eigen/Core>

using namespace MDConstants;
int main(int argc, char* argv[]){	// Args: n, dt, nue, temp_start [, glut-Optionen]

	Eigen::initParallel();
	
	int n;
	double dt;
	double nu;
	double temp_start;

	if (argc == 1){
		n = DEFAULT_PARTICLES;
		dt = DEFAULT_TIMESTEP;
		nu = DEFAULT_NU;
		temp_start = DEFAULT_TEMP_START;
	}
	else if (argc == 5){
		n = atoi(argv[1]);
		dt = atof(argv[2]);
		nu = atof(argv[3]);
		temp_start = atof(argv[4]);
	}
	else
		return 1;
	Eigen::setNbThreads(4);

	MDSimulation* sim = MDSimulation::GetSimulationInstance(DIMENSION, dt);
	StructureLogger logger(sim, "./output.txt"); 
	ThermoLogger tlogger(sim, "./outputoutput.txt"); 
	for (int i = 0; i < n; i++){
		MDParticle* particle = new MDParticle(DIMENSION);
		sim->particles->push_back(particle);
	}
	sim->getThermostat()->setT(temp_start);
	sim->getThermostat()->setNu(nu);
	sim->initSimulation(true, MDParticle::Vector::Ones(DIMENSION), nullptr, nullptr, 400, 0.15);
	
	sim->runSimulation(50);

	return 0;
	//return glutStuff(step, draw, reshape, keyboard, &argc, argv, sim, "MD - Basics");
}

