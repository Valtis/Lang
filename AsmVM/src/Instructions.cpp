#include "Instructions.h"
#include "VM.h"
#include "Tokens.h"
#include <stdexcept>

// Integer addition
void Instructions::I_Add(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command I_ADD");
		return;
	}

	int reg1 = GetRegisterNumber(params[1]);
	
	int reg2 = GetRegisterNumber(params[2]);
	int reg3 = GetRegisterNumber(params[3]);

	vm->m_registers[reg3].type = ObjectType::INTEGER;
	vm->m_registers[reg3].values.integer_value = vm->m_registers[reg1].values.integer_value + vm->m_registers[reg2].values.integer_value;
}

// Integer substraction
void Instructions::I_Sub(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command I_SUB");
		return;
	}

	int reg1 = GetRegisterNumber(params[1]);
	int reg2 = GetRegisterNumber(params[2]);
	int reg3 = GetRegisterNumber(params[3]);

	vm->m_registers[reg3].type = ObjectType::INTEGER;
	vm->m_registers[reg3].values.integer_value = vm->m_registers[reg1].values.integer_value - vm->m_registers[reg2].values.integer_value;
}

// moves value to a register
void Instructions::I_Mov(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 3)
	{
		throw std::runtime_error("Invalid parameter count for command I_MOV");
		return;
	}

	int reg1 = GetRegisterNumber(params[1]);
	int reg2 = GetRegisterNumber(params[2]);

	int value;

	if (reg1 == -1)
	{
		value = std::stoi(params[1]);
	}
	else
	{
		value = vm->m_registers[reg1].values.integer_value;
	}


	vm->m_registers[reg2].type = ObjectType::INTEGER;
	vm->m_registers[reg2].values.integer_value = value;
}



void Instructions::Print(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command PRINT");
	}

	VMObject &o = vm->m_registers[GetRegisterNumber(params[1])];

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
		printf("%d\n", *(int *)o.values.ptr.ptr);
		break;
	case ObjectType::DOUBLE_PTR:
		printf("%f\n", *(double *)o.values.ptr.ptr);
		break;
	case ObjectType::CHAR_PTR:
		printf("%c\n", *(char *)o.values.ptr.ptr);
		break;
	default:
		printf("**UNINITIALIZED**\n");
		break;
	}
}

void Instructions::GC(VM * vm, const std::vector<std::string> &params)
{
	vm->m_memoryManager.RunGC(vm);
}

void Instructions::I_Alloc(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 3)
	{
		throw std::runtime_error("Invalid parameter count for command I_ALLOC");
	}

	int cnt = std::stoi(params[1]);
	int reg = GetRegisterNumber(params[2]);

	VMObject o = vm->m_memoryManager.Allocate(vm, ObjectType::INTEGER_PTR, cnt);
	vm->m_registers[reg] = o;
}


void Instructions::Push(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command PUSH");
	}

	if (vm->m_stack_ptr == STACK_SIZE)
	{
		throw std::runtime_error("Stack overflow");
	}
	VMObject o;
	if (params[1] != NIL_TOKEN)
	{
		int reg = GetRegisterNumber(params[1]);
		o = vm->m_registers[reg];
	}

	vm->m_stack[vm->m_stack_ptr++] = o;
}

void Instructions::Pop(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command POP");
	}

	if (vm->m_stack_ptr == 0)
	{
		throw std::runtime_error("Stack underflow");
	}
	--vm->m_stack_ptr;
	
	if (params[1] != NIL_TOKEN)
	{
		int reg = GetRegisterNumber(params[1]);
		vm->m_registers[reg] = vm->m_stack[vm->m_stack_ptr];
	}
}


int Instructions::GetRegisterNumber(std::string param, bool throwOnInvalid)
{
	
	for (int i = 0; i < REGISTER_CNT; ++i)
	{
		std::string reg = REGISTER_START_TOKEN + std::to_string(i);
		if (reg == param)
		{
			return i;
		}
	}

	if (throwOnInvalid)
	{
		throw std::runtime_error("Invalid register: " + param);
	}

	return -1;
}

