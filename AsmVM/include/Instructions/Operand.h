#pragma once

#include "VM.h"

template <typename Type>
class Operand
{
public:
	Operand() : m_useRegister(false) 
	{
		memset(&value, 0, sizeof(value));
	}

	~Operand()
	{

	}

	void SetValue(Type val)
	{
		m_useRegister = false;
		value.m_value = val;
	}

	void SetRegister(int reg)
	{
		m_useRegister = true;
		if (reg < 0 || reg >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(reg));
		}
		value.m_register = reg;
	}
	
	Type GetValue(VM *vm)
	{
		if (!m_useRegister)	
		{
			return value.m_value;
		}

		return *(Type *)(&vm->m_registers[value.m_register].values);
	}
	
private:
	bool m_useRegister;
	union 
	{
		int m_register;
		Type m_value;
	} value;
};

