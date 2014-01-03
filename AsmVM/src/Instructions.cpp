#include "Instructions.h"
#include "VM.h"
#include "Tokens.h"
#include <stdexcept>

/*
}

void Instructions::GC(VM * vm, const std::vector<std::string> &params)
{
	vm->m_memoryManager.RunGC(vm);
}

void Instructions::MemManagerDebugPrint(VM * vm, const std::vector<std::string> &params)
{
	vm->m_memoryManager.DebugHeapPrint();
}


void Instructions::I_Alloc(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 3)
	{
		throw std::runtime_error("Invalid parameter count for command I_ALLOC");
	}

	int cnt = I_ValueHelper(vm, params[1]);
	int reg = GetRegisterNumber(params[2]);

	VMObject o = vm->m_memoryManager.Allocate(vm, ObjectType::INTEGER_PTR, cnt);
	vm->m_registers[reg] = o;
}


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


void Instructions::Push(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command PUSH");
	}


	VMObject o;
	if (params[1] != NIL_TOKEN)
	{
		int reg = GetRegisterNumber(params[1]);
		o = vm->m_registers[reg];
	}

	PushHelper(vm, o);
}


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
}



*/