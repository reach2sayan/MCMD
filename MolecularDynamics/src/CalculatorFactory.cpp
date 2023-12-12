#include "CalculatorFactory.hpp"
#include "LJCalculator.hpp"

CalculatorFactory::CalculatorFactory(){
	Register(CalculatorType::LJ, &LJCalculator::Create);
}

void CalculatorFactory::Register(const CalculatorType ctype, CreateCalculatorFunc pfnCreate){
	m_FactoryMap[ctype] = pfnCreate;
}

Calculator* CalculatorFactory::CreateCalculator(const CalculatorType ctype){
	typename FactoryMap::iterator it = m_FactoryMap.find(ctype);
	if (it != m_FactoryMap.end())
		return it->second();
	return nullptr;
}
