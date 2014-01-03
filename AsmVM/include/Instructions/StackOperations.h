#pragma once
#include "Instructions/Instruction.h"
#include "VM.h"

class Push : public Instruction
{
public:
	Push(int reg)
	{
		// -1 has a special meaning of pushing nil value into stack
		if (reg < -1 || reg >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(reg));
		}
		m_register = reg;
	}

	void Execute(VM *vm) override
	{
		if (m_register == -1)
		{
			VMObject o;
			o.values.integer_value = 0;
			o.type = ObjectType::UNINITIALIZED;
			vm->Push(o);
			return;
		}

		vm->Push(vm->m_registers[m_register]);

	}

private:
	int m_register;
};

class Pop : public Instruction
{
public:
	Pop(int reg)
	{
		// -1 has a special meaning of pushing nil value into stack
		if (reg < 0 || reg >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(reg));
		}
		m_register = reg;
	}

	void Execute(VM *vm) override
	{
		vm->m_registers[m_register] = vm->Pop();
	}

private:
	int m_register;
};

/*
void Instructions::Pop(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command POP");
	}

	VMObject o;
	PopHelper(vm, o);
	if (params[1] != NIL_TOKEN)
	{
		int reg = GetRegisterNumber(params[1]);
		vm->m_registers[reg] = o;
	}
}

void Instructions::StackRead(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 3)
	{
		throw std::runtime_error("Invalid parameter count for command STACKR");
	}

	int offset = std::stoi(params[1]);
	int reg = GetRegisterNumber(params[2]);

	unsigned int pos = vm->m_frame_ptr + offset;
	if (pos >= vm->m_stack.size())
	{
		throw std::runtime_error("STACKR stack overflow");
	}

	if (pos < 0)
	{
		throw std::runtime_error("STACKR stack underflow");
	}

	vm->m_registers[reg] = vm->m_stack[pos];
}

void Instructions::StackWrite(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 3)
	{
		throw std::runtime_error("Invalid parameter count for command STACKW");
	}

	int offset = std::stoi(params[1]);
	int reg = GetRegisterNumber(params[2]);

	unsigned int pos = vm->m_frame_ptr + offset;
	if (pos >= vm->m_stack.size())
	{
		throw std::runtime_error("STACKR stack overflow");
	}

	if (pos < 0)
	{
		throw std::runtime_error("STACKR stack underflow");
	}

	vm->m_stack[pos] = vm->m_registers[reg];
*/