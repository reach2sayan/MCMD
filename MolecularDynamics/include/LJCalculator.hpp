#include "Calculator.hpp"

template<int D>
class LJCalculator : public Calculator<D> {

	private:
	public:

		typename MDParticle<D>::Vector ForceFunc(const typename MDParticle<D>::Vector& r);
		double PotentialFunc(const typename MDParticle<D>::Vector& r);

		static Calculator<D>* Create() { return new LJCalculator<D>(); }
};
