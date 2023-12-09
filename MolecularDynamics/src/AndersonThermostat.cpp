#include "AndersonThermostat.hpp"
#include "MDSimulation.hpp"
#include <random>

constexpr double TWOPI = 2 * M_PI;
constexpr auto N = 624;
constexpr auto M = 397;
constexpr auto HI = 0x80000000;
constexpr auto LO = 0x7fffffff;
constexpr auto MAX = 0xFFFFFFFF;
//std::mt19937_64 mersenneTwister{};

double mersenneTwister();

template<int D>
void AndersonThermostat<D>::execute(){

	if (sim->pause)
		return;

	for (auto& particle : *(sim->particles)){

		double u1 = log(1.0 - mersenneTwister());
		double u2 = TWOPI * mersenneTwister();
		int dim = sim->getDim();
		double s = sin(u2), c = cos(u2);
		switch(dim){
			case 2:
				particle->v[0] = std::sqrt(temp*u1)*c;
				particle->v[1] = std::sqrt(temp*u1)*s;
				break;
			case 3:
				double u3 = M_PI * mersenneTwister();
				double s_ = sin(u3), c_ = cos(u3);
				particle->v[0] = std::sqrt(temp*u1)*s_*c_;
				particle->v[1] = std::sqrt(temp*u1)*s_*s_;
				particle->v[2] = std::sqrt(temp*u1)*c_;
				break;
		}
	}
}
double mersenneTwister(){
	static constexpr uint32_t seed = 5489UL;
	static constexpr uint32_t A[2] = { 0, 0x9908b0df };
	static uint32_t y[N];
	static int i = N + 1;

	if (i > N) {
		//initialize y with pseudo random numbers
		y[0] = seed;

		for (i = 1; i < N; ++i) 
			y[i] = (1812433253UL * (y[i - 1] ^ (y[i - 1] >> 30)) + i);
	}

	if (i == N) {
		//calculate new state vector
		uint32_t h;

		for (i = 0; i < N - M; ++i) {
			h = (y[i] & HI) | (y[i + 1] & LO);
			y[i] = y[i + M] ^ (h >> 1) ^ A[h & 1];
		}
		for (; i < N - 1; ++i) {
			h = (y[i] & HI) | (y[i + 1] & LO);
			y[i] = y[i + (M - N)] ^ (h >> 1) ^ A[h & 1];
		}
		
		h = (y[N - 1] & HI) | (y[0] & LO);
		y[N - 1] = y[M - 1] ^ (h >> 1) ^ A[h & 1];
		i = 0;
	}

	uint32_t e = y[i++];
	//tempering
	e ^= (e >> 11);
	e ^= (e << 7) & 0x9d2c5680;
	e ^= (e << 15) & 0xefc60000;
	e ^= (e >> 18);

	return static_cast<double>(e) / MAX;
}

template<int D>
inline AndersonThermostat<D>::AndersonThermostat(MDSimulation<D>* sim, double temp, double nu) :
	sim{sim}, temp{temp}, nu{-nu} {
		p = 1 - exp(nu*sim->getDt());
	}

template<int D>
inline void AndersonThermostat<D>::setNu(const double nu_){
	nu = (-1.0)*nu_;
	p = 1 - exp(nu_*sim->getDt());
}

template<int D>
inline double AndersonThermostat<D>::getNu() const {
	return (-1.0)*nu;
}

template<int D>
inline void AndersonThermostat<D>::setT(const double temp) { 
	this->temp = -2.0*temp;
}

template<int D>
inline double AndersonThermostat<D>::getT() const {
	return 0.5*temp;
}
template class AndersonThermostat<2>;
