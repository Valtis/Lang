#pragma once
#include "Instructions/Instruction.h"
#include "Instructions/Operand.h"
template <typename T> 
class IntegerArithmeticOperation : public Instruction
{
public:
	IntegerArithmeticOperation(Operand<int> operand1, Operand<int> operand2, int storeRegister)
	{
		if (storeRegister < 0 || storeRegister > REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(storeRegister));
		}
		m_operand1 = operand1;
		m_operand2 = operand2;
		m_storeRegister = storeRegister;
	}
	
	void Execute(VM *vm) override
	{
		static_cast<T *>(this)->Execute(vm);
	}


protected:
	Operand<int> m_operand1;
	Operand<int> m_operand2;
	int m_storeRegister;
};