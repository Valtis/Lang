#pragma once
#include "Instructions/Instruction.h"
#include "Instructions/Operand.h"
#include "Instructions/TypeSetters.h"

template <typename T>
class Compare : public Instruction
{
public:
	Compare(Operand<T> op1, Operand<T> op2)
	{
		m_op1 = op1;
		m_op2 = op2;
	}

	void Execute(VM *vm)
	{
		vm->m_cmpResult = CmpResult::GREATER;
		T val1 = m_op1.GetValue(vm);
		T val2 = m_op2.GetValue(vm);
		
		if (val1 < val2)
		{
			vm->m_cmpResult = CmpResult::LESSER;
		}
		else if (val1 == val2)
		{
			vm->m_cmpResult = CmpResult::EQUAL;
		}
	}


private:
	Operand<T> m_op1;
	Operand<T> m_op2;
};

template <typename T>
class Move : public Instruction
{
public:
	Move(Operand<T> op1, int storeRegister)
	{
		m_op1 = op1;

		if (storeRegister < 0 || storeRegister >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(storeRegister));
		}

		m_storeRegister = storeRegister;
	}

	void Execute(VM *vm)
	{
		*((T*)(&vm->m_registers[m_storeRegister].values)) = m_op1.GetValue(vm);		
		TypeSetter::SetType<T>(vm->m_registers[m_storeRegister]);
	}


private:
	Operand<T> m_op1;
	int m_storeRegister;
};

