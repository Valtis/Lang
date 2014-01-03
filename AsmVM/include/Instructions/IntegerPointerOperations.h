#pragma once
#include "Instructions/Instruction.h"
#include "VM.h"
#include "Instructions/Operand.h"

class AllocateIntegerPointer : public Instruction
{
public:
	AllocateIntegerPointer(Operand<int> size, int reg)
	{
		if (reg < 0 || reg > REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(reg));
		}

		m_register = reg;
		m_size = size;
	}

	void Execute(VM *vm) override
	{
		vm->m_registers[m_register] = vm->m_memoryManager.Allocate(vm, ObjectType::INTEGER_PTR, m_size.GetValue(vm));
	}

private:
	Operand<int> m_size;
	int m_register;

};

/*




void Instructions::I_ptr_write(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command IPW");
	}

	int value = I_ValueHelper(vm, params[1]);
	unsigned int pos = I_ValueHelper(vm, params[2]);
	int reg = GetRegisterNumber(params[3]);

	if (!IsPointer(vm->m_registers[reg]))
	{
		throw std::runtime_error("Pointer operation on nonpointer type attempted");
	}

	int *ptr = (int *)vm->m_registers[reg].values.ptr.ptr;
	int ptrSize = vm->m_registers[reg].values.ptr.size;
	if (pos < 0)
	{
		throw std::runtime_error("Pointer write underflow " + std::to_string(pos));
	}
	else if (pos >= ptrSize / sizeof(int))
	{
		throw std::runtime_error("Pointer write overflow: write to index " + std::to_string(pos) + " max: " + std::to_string(ptrSize / sizeof(int)-1));
	}

	if (ptr == nullptr)
	{
		throw std::runtime_error("Nullpointer dereferenced");
	}

	ptr[pos] = value;

}

void Instructions::I_ptr_read(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command IPR");
	}

	int srcReg = GetRegisterNumber(params[1]);
	int pos = I_ValueHelper(vm, params[2]);
	int destReg = GetRegisterNumber(params[3]);


	if (!IsPointer(vm->m_registers[srcReg]))
	{
		throw std::runtime_error("Pointer operation on nonpointer type attempted");
	}

	int *ptr = (int *)vm->m_registers[srcReg].values.ptr.ptr;
	int ptrSize = vm->m_registers[srcReg].values.ptr.size;

	if (ptr == nullptr)
	{
		throw std::runtime_error("Nullpointer dereferenced");
	}

	if (pos < 0)
	{
		throw std::runtime_error("Pointer read underflow: index " + std::to_string(pos));
	}
	else if (pos >= ptrSize / sizeof(int))
	{
		throw std::runtime_error("Pointer read overflow: read from index " + std::to_string(pos) + " max: " + std::to_string(ptrSize / sizeof(int)-1));
	}

	vm->m_registers[destReg].type = ObjectType::INTEGER;
	vm->m_registers[destReg].values.integer_value = ptr[pos];
}
*/