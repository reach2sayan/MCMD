#include <cmath>
namespace MDConstants {
	const double SQR_2_5 = std::pow(2.0, 0.2);
	const double SIGMA_6 = std::pow(0.025, 6.0);
	constexpr int HISTOGRAM_RESOLUTION = 201;
	constexpr double TWOPI = 2 * M_PI;
	constexpr auto N = 624;
	constexpr auto M = 397;
	constexpr auto HI = 0x80000000;
	constexpr auto LO = 0x7fffffff;
	constexpr auto MAX = 0xFFFFFFFF;
	constexpr int DEFAULT_PARTICLES = 2;
	constexpr double DEFAULT_TIMESTEP = 0.001;
	constexpr double DEFAULT_NU = 10;
	constexpr double DEFAULT_TEMP_START = 0.1;
	constexpr int DIMENSION = 2;
}
