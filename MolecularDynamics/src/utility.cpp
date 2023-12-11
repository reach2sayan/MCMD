#include "utility.hpp"

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
