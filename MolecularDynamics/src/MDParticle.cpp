#include "MDParticle.hpp"

MDParticle::MDParticle(const int dim_) : 
	dim(dim_),
	r(Vector::Zero(dim_)),
	v(Vector::Zero(dim_)),
	a(Vector::Zero(dim_)),
	verletList(std::make_unique<MDParticleList>())
{}

MDParticle::MDParticle(const Vector& r_, const Vector& v_) :
	dim(r_.size()),
	r(r_),
	v(v_),
	verletList(std::make_unique<MDParticleList>())
{}
