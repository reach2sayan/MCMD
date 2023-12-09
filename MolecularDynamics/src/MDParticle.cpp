#include "MDParticle.hpp"

template<int D>
MDParticle<D>::MDParticle() : 
	dim{D},
	r{Vector::Zero(D)},
	v{Vector::Zero(D)},
	a{Vector::Zero(D)},
	verletList(std::make_unique<MDParticleList<D>>())
{}

template<int D>
MDParticle<D>::MDParticle(const Vector& r_, const Vector& v_) :
	dim(r_.size()),
	r(r_),
	v(v_),
	verletList(std::make_unique<MDParticleList<D>>())
{}
template class MDParticle<2>;
