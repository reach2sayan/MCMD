#ifndef __MDLOGGER__
#define __MDLOGGER__

class MDSimulation;
class Logger {

	public:
		virtual ~Logger() {};
		virtual void log() const = 0;
};

class StructureLogger : public Logger {
	
	public:
		StructureLogger(MDSimulation& sim_);
	  void log() const override;
	
	private:
		MDSimulation& sim;
};
#endif
