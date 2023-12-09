#ifndef __MDPARTICLE_HPP__
#define __MDPARTICLE_HPP__

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
	#ifndef __EIGEN__
	#include <eigen3/Eigen/Dense>
	#endif
#endif

#include <memory>
#include <vector>

template<int D>
class MDParticle;

template<int D>
using MDParticleList = std::vector<MDParticle<D>*>;

template <int D>
class MDParticle{

	public:
		using Vector = Eigen::Matrix<double, D, 1>;
		using Matrix = Eigen::Matrix<double, D, D>;
		enum { NeedsToAlign = (sizeof(Vector)%16)==0 };

	public:
		explicit MDParticle();
		MDParticle(const Vector& r_, const Vector& v_);
		~MDParticle() = default;
		
		int dim = 2;
		Vector r, v, a;
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF(NeedsToAlign)
		std::unique_ptr<MDParticleList<D>> verletList;
};
#endif
