#ifndef __MDLOGGER__
#define __MDLOGGER__

#include <iostream>
#include <fstream>
#include <string>
class MDSimulation;
class Logger {

	public:
		virtual ~Logger() {};
		virtual void log() const = 0;
};

class StructureLogger : public Logger {
	
	public:
		StructureLogger(MDSimulation* sim_, std::string&& filename);
	  void log() const override;
		~StructureLogger() noexcept;
	
	private:
		std::ofstream myfile;
		MDSimulation* sim;
};

class ThermoLogger : public Logger {

	public:
		ThermoLogger(MDSimulation* sim, std::string&& filename);
		void log() const override;
		~ThermoLogger() noexcept;

	private:
		std::ofstream myfile;
		MDSimulation* sim;
};
#endif
