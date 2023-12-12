#include "CalculatorFactory.hpp"

class LJCalculator : public Calculator {

	public:

		Vector ForceFunc(const Vector& r);
		double PotentialFunc(const Vector& r);

		static Calculator* Create() { return new LJCalculator(); }
};
