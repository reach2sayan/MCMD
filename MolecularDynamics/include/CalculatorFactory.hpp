#ifndef __CALCULATORFACTORY_HPP__
#define __CALCULATORFACTORY_HPP__

#include "MDParticle.hpp"
#include <unordered_map>

enum CalculatorType {LJ};

class Calculator {
	public:
		using Vector = typename MDParticle::Vector;
		virtual Vector ForceFunc(const Vector& r) = 0;
		virtual double PotentialFunc(const Vector& r) = 0;
};

using CreateCalculatorFunc = Calculator*(*)(void);

class CalculatorFactory {

	private:
		CalculatorFactory();
		CalculatorFactory(const CalculatorFactory&) = delete;
		CalculatorFactory& operator=(const CalculatorFactory&) = delete;

		using FactoryMap = std::unordered_map<CalculatorType,CreateCalculatorFunc>;
		FactoryMap m_FactoryMap;

	public:
		~CalculatorFactory() { m_FactoryMap.clear(); }

		static CalculatorFactory* Get(){
			static CalculatorFactory instance;
			return &instance;
		}

		void Register(const CalculatorType ctype, CreateCalculatorFunc pfnCreate);
		Calculator* CreateCalculator(const CalculatorType ctype);
};

#endif
