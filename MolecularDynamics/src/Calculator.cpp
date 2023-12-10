#include "Calculator.hpp"
#include "LJCalculator.hpp"

template<int D>
CalculatorFactory<D>::CalculatorFactory(){
	Register(CalculatorType::LJ, &LJCalculator<D>::Create);
}

template<int D>
void CalculatorFactory<D>::Register(const CalculatorType ctype, CreateCalculatorFunc<D> pfnCreate){
	m_FactoryMap[ctype] = pfnCreate;
}

template<int D>
Calculator<D>* CalculatorFactory<D>::CreateCalculator(const CalculatorType ctype){
	typename FactoryMap::iterator it = m_FactoryMap.find(ctype);
	if (it != m_FactoryMap.end())
		return it->second();
	return nullptr;
}
template class CalculatorFactory<2>;
