#pragma once
#include "Instructions/Instruction.h"
#include "Instructions/Operand.h"
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

class ReadStack : public Instruction
{
public:
	ReadStack(Operand<int> offset, int storeRegister)
	{
		// -1 has a special meaning of pushing nil value into stack
		if (storeRegister < 0 || storeRegister >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(storeRegister));
		}
		m_register = storeRegister;
		m_offset = offset;
	}

	void Execute(VM *vm) override
	{
		long int pos = vm->m_frame_ptr + m_offset.GetValue(vm);
		if (pos >= STACK_SIZE || pos >= vm->m_stack_ptr)
		{
			throw std::runtime_error("Stack Read reading over stack pointer");
		}

		if (pos < 0)
		{
			throw std::runtime_error("Stack read reading under stack");
		}

		vm->m_registers[m_register] = vm->m_stack[pos];	
	}

private:
	Operand<int> m_offset;
	int m_register;
};

class WriteStack : public Instruction
{
public:
	WriteStack(Operand<int> offset, int storeRegister)
	{
		// -1 has a special meaning of pushing nil value into stack
		if (storeRegister < 0 || storeRegister >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(storeRegister));
		}
		m_register = storeRegister;
		m_offset = offset;
	}

	void Execute(VM *vm) override
	{
		long int pos = vm->m_frame_ptr + m_offset.GetValue(vm);
		if (pos >= STACK_SIZE || pos >= vm->m_stack_ptr)
		{
			throw std::runtime_error("Stack write writing over stack pointer");
		}

		if (pos < 0)
		{
			throw std::runtime_error("Stack write writing under stack");
		}
		
		vm->m_stack[pos] = vm->m_registers[m_register];
	}

private:
	Operand<int> m_offset;
	int m_register;
};


