#include "LJCalculator.hpp"
#
#include "constants.hpp"

inline LJCalculator::Vector LJCalculator::ForceFunc(const Vector& r){
	double r2 = r.squaredNorm();
	double r4 = r2*r2;
	double r8 = r4*r4;
	return 24.0 * MDConstants::SIGMA_6 * ((2 * MDConstants::SIGMA_6) / (r8*r4*r2) - 1 / r8) * r;
}

inline double LJCalculator::PotentialFunc(const Vector& r){
	double r2 = r.squaredNorm();
	double r4 = r2*r2;
	return 4.0 * MDConstants::SIGMA_6 * (MDConstants::SIGMA_6 / (r4*r4*r4) - 1 / (r4*r2));
}
