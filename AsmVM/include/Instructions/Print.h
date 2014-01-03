#pragma once
#include "Instructions/Instruction.h"
#include "VM.h"
#include <cstdio>
class Print : public Instruction
{
public:
	Print(std::vector<std::string> tokens) : m_printRegister(false)
	{
		// dirty hack, needs to be fixed!
	
		for (unsigned int i = 1; i < tokens.size(); ++i)
		{

			if (i == 1)
			{
				m_string = tokens[1].substr(1, tokens[1].length()).c_str();
			}
			else
			{
				m_string += " " + tokens[i];
			}
		}
	}
	
	Print(int reg) : m_printRegister(true)
	{
		if (reg < 0 || reg > REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(reg));
		}
		m_register = reg;
	}

	void Execute(VM *vm)
	{

		if (!m_printRegister)
		{
			puts((m_string + "\n").c_str());
			return;
		}

		VMObject &o = vm->m_registers[m_register];

		switch (o.type)
		{
		case ObjectType::INTEGER:

			printf("%d\n", o.values.integer_value);
			break;
		case ObjectType::DOUBLE:
			printf("%f\n", o.values.double_value);
			break;
		case ObjectType::CHAR:
			printf("%c\n", o.values.char_value);
			break;
		case ObjectType::INTEGER_PTR:
		case ObjectType::DOUBLE_PTR:
		case ObjectType::CHAR_PTR:
			printf("%d\n", o.values.ptr.ptr); // print memory address
			break;
		default:
			printf("**UNINITIALIZED**\n");
			break;
		}
	}

private:
	bool m_printRegister;
	int m_register;
	std::string m_string;
};