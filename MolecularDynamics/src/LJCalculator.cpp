#include "LJCalculator.hpp"
#include "constants.hpp"

template<int D>
inline typename MDParticle<D>::Vector LJCalculator<D>::ForceFunc(const typename MDParticle<D>::Vector& r){
	double r2 = r.squaredNorm();
	double r4 = r2*r2;
	double r8 = r4*r4;
	return 24.0 * MDConstants::SIGMA_6 * ((2 * MDConstants::SIGMA_6) / (r8*r4*r2) - 1 / r8) * r;
}

template<int D>
inline double LJCalculator<D>::PotentialFunc(const typename MDParticle<D>::Vector& r){
	double r2 = r.squaredNorm();
	double r4 = r2*r2;
	return 4.0 * MDConstants::SIGMA_6 * (MDConstants::SIGMA_6 / (r4*r4*r4) - 1 / (r4*r2));
}
template class LJCalculator<2>;
