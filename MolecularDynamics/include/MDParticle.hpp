#ifndef __MDPARTICLE_HPP__
#define __MDPARTICLE_HPP__
#define eigen_assert(X) do { if(!(X)) throw std::runtime_error(#X); } while(false);
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
	#ifndef __EIGEN__
	#include <eigen3/Eigen/Dense>
	#endif
#endif

#include <memory>
#include <vector>

class MDParticle;

using MDParticleList = std::vector<MDParticle*>;

class MDParticle{

	public:
		using Vector = Eigen::Matrix<double, Eigen::Dynamic , 1>;
		using Matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
		enum { NeedsToAlign = (sizeof(Vector)%16)==0 };

	public:
		MDParticle() = delete;
		explicit MDParticle(const int dim);
		MDParticle(const Vector& r_, const Vector& v_);
		~MDParticle() = default;
		
		int dim = 2;
		Vector r, v, a;
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF(NeedsToAlign)
		std::unique_ptr<MDParticleList> verletList;
};
#endif
