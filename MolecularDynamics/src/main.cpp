#include "Calculator.hpp"
#include "MDSimulation.hpp"
#include "AndersonThermostat.hpp"
#include "glutSetup2d.hpp"

constexpr int DEFAULT_PARTICLES = 2;
constexpr double DEFAULT_TIMESTEP = 0.001;
constexpr double DEFAULT_NU = 10;
constexpr double DEFAULT_TEMP_START = 0.1;
constexpr int DIMENSION = 2;

int main(int argc, char* argv[]){	// Args: n, dt, nue, temp_start [, glut-Optionen]
	
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

	std::unique_ptr<MDSimulation<DIMENSION>> sim = std::make_unique<MDSimulation<DIMENSION>>(DIMENSION, dt, CalculatorType::LJ , 0.15, 0.22, 10);
	for (int i = 0; i < n; i++){
		MDParticle<DIMENSION>* particle = new MDParticle<DIMENSION>();
		sim->particles->push_back(particle);
	}

	sim->getThermostat()->setT(temp_start);
	sim->getThermostat()->setNu(nu);

	MDParticle<DIMENSION>::Vector arr1 = MDParticle<DIMENSION>::Vector::Ones();
	sim->initSimulation(true, arr1, nullptr, nullptr, 400, 0.15);

	return glutStuff(step<DIMENSION>, draw<DIMENSION>, reshape, keyboard<DIMENSION>, &argc, argv, sim.get(), "MD - Basics");
}

