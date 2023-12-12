#ifndef __MDSIMULATION_HPP__
#define __MDSIMULATION_HPP__

#include "MDParticle.hpp"
#include "CalculatorFactory.hpp"
#include "AndersonThermostat.hpp"
#include "ThermostatFactory.hpp"
#include "utility.hpp"
#include <list>

using namespace MDConstants;
typedef struct graphData_t{
	double eKin, ePot;
	graphData_t* next;
} graphData_t;

class Logger;
class MDSimulation{

	public:
		using Vector = typename MDParticle::Vector;
		using Matrix = typename MDParticle::Matrix;
		using MatrixHistogram = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
		using VectorHistogram = Eigen::Matrix<double, Eigen::Dynamic, 1>;
		using InitPositionFunc = Vector(*)(int);
		using InitVelocityFunc = InitPositionFunc;
	
	private:
		MDSimulation(int dim_ = 2, double dt = DEFAULT_TIMESTEP, CalculatorType ctype = CalculatorType::LJ, ThermostatType ttype = ThermostatType::ANDERSON, double r_inter = DEFAULT_R_INTER, double r_verlet = DEFAULT_R_VERLET, int verletUpdate = DEFAULT_VERLET_UPDATE);
		static MDSimulation* instance;

	public:
		~MDSimulation() = default;
		MDSimulation(const MDSimulation&) = delete;
    MDSimulation& operator=(const MDSimulation&) = delete;

		static MDSimulation* GetSimulationInstance(int dim = 2, double dt = DEFAULT_TIMESTEP, CalculatorType ctype = CalculatorType::LJ, ThermostatType ttype = ThermostatType::ANDERSON, double r_inter = DEFAULT_R_INTER, double r_verlet = DEFAULT_R_VERLET, int verletUpdate = DEFAULT_VERLET_UPDATE);
		void initSimulation(bool periodic_, const Vector simBox_ , InitPositionFunc r0_, InitVelocityFunc v0_, int histogramResolution_ , double histogramLength_ = 0.5);
		void velocityVerletStep(bool);
		void updateGraphs();
		void resetGraphs();

		void resetRadialDistribution() { radial *= 0.0; }
		VectorHistogram getRadialDistribution() const {return radial.normalized(); }
		int getHistogramResolution() const { return histogramResolution; }

		void resetDirectionalDistribution() { directional = MatrixHistogram::Zero(histogramResolution,histogramResolution); }
		MatrixHistogram getDirectionalDistribution() const;

		double getDt() const { return dt; }
		double getT() const { return t; }
		int getDim() const { return dim; }
		double getEPotMin() const { return ePotMin; }
		Thermostat* getThermostat() { return thermo; }

		std::unique_ptr<MDParticleList> particles;
		bool pause;
		graphData_t *graphDataFirst, *graphDataLast; // graphDataFirst contains max values and leads to values for t=0

		void registerLogger(Logger* logger) { loggers.push_back(logger); }
		void unregisterLogger(Logger* logger) { loggers.remove(logger); }

		void log() const;

	private:
		double refreshVerletLists(bool, bool);
		double velocityVerletForce();
		void ApplyPeriodicBoundaryCondition(MDParticle* particle);

		Thermostat* thermo;
		Calculator* calculator;
		double dt, t, r_inter, r_verlet, eKin, ePot, ePotMin, histogramLength;
		Vector simBox;
		VectorHistogram radial;
		MatrixHistogram directional;
		int verletSteps, verletUpdate, dim, histogramResolution;
		bool periodic;

		std::list<Logger*> loggers;
};

#endif
