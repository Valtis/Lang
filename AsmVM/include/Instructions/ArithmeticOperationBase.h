#pragma once
#include "Instructions/Instruction.h"
#include "Instructions/Operand.h"
#include <type_traits>

template <typename Type, typename Derived> 
class ArithmeticOperationBase : public Instruction
{
public:
	ArithmeticOperationBase(Operand<Type> operand1, Operand<Type> operand2, int storeRegister)
	{
		if (storeRegister < 0 || storeRegister >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(storeRegister));
		}
		m_operand1 = operand1;
		m_operand2 = operand2;
		m_storeRegister = storeRegister;
	}
	
	void Execute(VM *vm) override
	{
		static_cast<Derived *>(this)->Execute(vm);
	}



protected:
	Operand<Type> m_operand1;
	Operand<Type> m_operand2;
	int m_storeRegister;
};