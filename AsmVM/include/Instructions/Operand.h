#pragma once

template <typename T>
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

	void SetValue(T value)
	{
		m_useRegister = false;
		value->m_value = value;
	}

	void SetRegister(int reg)
	{
		m_useRegister = true;
		if (reg < 0 || reg >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(reg));
		}
		value->m_register = reg;
	}
	
	T GetValue(VM *vm)
	{
		if (!m_useRegister)	
		{
			return value.m_value;
		}
		
		return *(T *)(vm->m_registers[value.m_register]);
	}
	
private:
	bool m_useRegister;
	union 
	{
		int m_register;
		T m_value;
	} value;
};

