#pragma once
#include "Instructions/Instruction.h"
#include "VM.h"
#include "Instructions/Operand.h"

class AllocateIntegerPointer : public Instruction
{
public:
	AllocateIntegerPointer(Operand<int> size, int reg)
	{
		if (reg < 0 || reg >= REGISTER_CNT)
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

class WriteToIntegerPointer : public Instruction
{
public:
	WriteToIntegerPointer(Operand<int> value, Operand<int> location, int storeRegister)
	{
		if (storeRegister < 0 || storeRegister >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(storeRegister));
		}
		m_value = value;
		m_register = storeRegister;
		m_location = location;		
	}

	void Execute(VM *vm) override
	{
		if (!IsPointer(vm->m_registers[m_register]))
		{
			throw std::runtime_error("Pointer operation on non pointer type attempted");
		}

		int *ptr = (int *)vm->m_registers[m_register].values.ptr->ptr;
		int ptrSize = vm->m_registers[m_register].values.ptr->size;
		
		int pos = m_location.GetValue(vm);
		
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
			throw std::runtime_error("Null pointer dereferenced");
		}

		ptr[pos] = m_value.GetValue(vm);

	}

private:
	Operand<int> m_value;
	Operand<int> m_location;
	int m_register;
};

class ReadFromIntegerPointer : public Instruction
{
public:
	ReadFromIntegerPointer(int sourceRegister, Operand<int> location, int storeRegister)
	{

		if (sourceRegister < 0 || sourceRegister >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(sourceRegister));
		}

		if (storeRegister < 0 || storeRegister >= REGISTER_CNT)
		{
			throw std::runtime_error("Invalid register specified: " + std::to_string(storeRegister));
		}
		m_sourceRegister = sourceRegister;
		m_destinationRegister = storeRegister;
		m_location = location;
	}

	void Execute(VM *vm) override
	{
		if (!IsPointer(vm->m_registers[m_sourceRegister]))
		{
			throw std::runtime_error("Pointer operation on non pointer type attempted");
		}

		int *ptr = (int *)vm->m_registers[m_sourceRegister].values.ptr->ptr;
		int ptrSize = vm->m_registers[m_sourceRegister].values.ptr->size;

		int pos = m_location.GetValue(vm);

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
			throw std::runtime_error("Null pointer dereferenced");
		}
		vm->m_registers[m_destinationRegister].type = ObjectType::INTEGER;
		vm->m_registers[m_destinationRegister].values.integer_value = ptr[pos];
	}

private:
	int m_sourceRegister;
	Operand<int> m_location;
	int m_destinationRegister;
};





