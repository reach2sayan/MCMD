#ifndef __CALCULATOR_HPP__
#define __CALCULATOR_HPP__

#include <map>
#include "MDParticle.hpp"

enum CalculatorType {LJ};

template<int D>
class Calculator {
	public:
		virtual typename MDParticle<D>::Vector ForceFunc(const typename MDParticle<D>::Vector& r) = 0;
		virtual double PotentialFunc(const typename MDParticle<D>::Vector& r) = 0;
};

template<int D>
using CreateCalculatorFunc = Calculator<D>*(*)(void);

template<int D>
class CalculatorFactory {

	private:
		CalculatorFactory();
		CalculatorFactory(const CalculatorFactory&) = delete;
		CalculatorFactory& operator=(const CalculatorFactory&) = delete;

		using FactoryMap = std::map<CalculatorType,CreateCalculatorFunc<D>>;
		FactoryMap m_FactoryMap;

	public:
		~CalculatorFactory() { m_FactoryMap.clear(); }

		static CalculatorFactory* Get(){
			static CalculatorFactory instance;
			return &instance;
		}

		void Register(const CalculatorType ctype, CreateCalculatorFunc<D> pfnCreate);
		Calculator<D>* CreateCalculator(const CalculatorType ctype);
};












#endif
