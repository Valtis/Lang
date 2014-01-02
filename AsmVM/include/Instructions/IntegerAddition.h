#pragma once
#include "VM.h"

#include "Instructions\IntegerArithmeticOperation.h"

class IntegerAddition : public IntegerArithmeticOperation<IntegerAddition>
{
public:
	IntegerAddition(Operand<int> operand1, Operand<int> operand2, int storeRegister) :
		IntegerArithmeticOperation(operand1, operand2, storeRegister)
	{

	}

	void Execute(VM *vm)
	{
		VMObject o;
		o.type = ObjectType::INTEGER;
		o.values.integer_value = m_operand1.GetValue(vm) + m_operand2.GetValue(vm);
		vm->m_registers[m_storeRegister] = o;
	}
};
