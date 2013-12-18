#include "Instructions.h"
#include "VM.h"
#include "Tokens.h"
#include <stdexcept>

// Integer addition

int Instructions::I_ValueHelper(VM *vm, std::string param)
{
	int reg = GetRegisterNumber(param, false);
	int val;
	if (reg != -1)
	{
		val = vm->m_registers[reg].values.integer_value;
	}
	else
	{
		val = std::stoi(param);
	}
	return val;
}

void Instructions::ArithmeticOperationHelper(VM *vm, const std::vector<std::string> &params, int &destReg, int &val1, int &val2)
{
	destReg = GetRegisterNumber(params[3]);
	val1 = I_ValueHelper(vm, params[1]);
	val2 = I_ValueHelper(vm, params[2]);
}

void Instructions::I_Add(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command I_ADD");
		return;
	}

	int val1;
	int val2;
	int reg;
	ArithmeticOperationHelper(vm, params, reg, val1, val2);

	vm->m_registers[reg].type = ObjectType::INTEGER;
	vm->m_registers[reg].values.integer_value = val1 + val2;
}

// Integer substraction
void Instructions::I_Sub(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command I_SUB");
		return;
	}

	int val1;
	int val2;
	int reg;
	ArithmeticOperationHelper(vm, params, reg, val1, val2);

	vm->m_registers[reg].type = ObjectType::INTEGER;
	vm->m_registers[reg].values.integer_value = val1 - val2;
}

// Integer mul
void Instructions::I_Mul(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command I_MUL");
		return;
	}

	int val1;
	int val2;
	int reg;
	ArithmeticOperationHelper(vm, params, reg, val1, val2);

	vm->m_registers[reg].type = ObjectType::INTEGER;
	vm->m_registers[reg].values.integer_value = val1 * val2;
}

// Integer div
void Instructions::I_Div(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command I_DIV");
		return;
	}

	int val1;
	int val2;
	int reg;
	ArithmeticOperationHelper(vm, params, reg, val1, val2);

	if (val2 == 0)
	{
		throw std::runtime_error("Division by zero");
	}

	vm->m_registers[reg].type = ObjectType::INTEGER;
	vm->m_registers[reg].values.integer_value = val1 / val2;
}

void Instructions::I_Rand(VM *vm, const std::vector<std::string> &params)
{
	if (params.size() != 4)
	{
		throw std::runtime_error("Invalid parameter count for command I_RAND");
		return;
	}

	int val1;
	int val2;
	int reg;
	ArithmeticOperationHelper(vm, params, reg, val1, val2);

	vm->m_registers[reg].type = ObjectType::INTEGER;

	std::uniform_int_distribution<int> dist(val1, val2);
	vm->m_registers[reg].values.integer_value = dist(vm->m_generator);
}

// moves value to a register
void Instructions::I_Cmp(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 3)
	{
		throw std::runtime_error("Invalid parameter count for command I_CMP");
		return;
	}
	int val1 = I_ValueHelper(vm, params[1]);
	int val2 = I_ValueHelper(vm, params[2]);

	vm->m_cmpResult = CmpResult::GREATER;

	if (val1 < val2)
	{
		vm->m_cmpResult = CmpResult::LESSER;
	}
	else if (val1 == val2)
	{
		vm->m_cmpResult = CmpResult::EQUAL;
	}
}

// moves value to a register
void Instructions::I_Mov(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 3)
	{
		throw std::runtime_error("Invalid parameter count for command I_MOV");
		return;
	}

	int reg1 = GetRegisterNumber(params[1], false);
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
	if (params.size() < 2 || (params.size() > 2 && params[1][0] != '@'))
	{
		throw std::runtime_error("Invalid parameter count for command PRINT");
	}
	// dirty hack, needs to be fixed!
	if (params[1][0] == '@')
	{

		for (int i = 1; i < params.size(); ++i)
		{

			if (i == 1)
			{
				printf("%s", params[1].substr(1, params[1].length()).c_str());
			}
			else
			{

				printf(" %s", params[i].c_str());
			}
		}
		printf("\n");

		return;
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
	case ObjectType::DOUBLE_PTR:
	case ObjectType::CHAR_PTR:

		printf("%d\n", o.values.ptr.ptr); // print memory address
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
	int pos = I_ValueHelper(vm, params[2]);
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
		throw std::runtime_error("Nullpointer referenced");
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
		throw std::runtime_error("Nullpointer referenced");
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


void Instructions::PushHelper(VM *vm, VMObject &obj)
{
	if (vm->m_stack_ptr == STACK_SIZE)
	{
		throw std::runtime_error("Stack overflow");
	}
	vm->m_stack[vm->m_stack_ptr++] = obj;

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

void Instructions::PopHelper(VM *vm, VMObject &obj)
{
	if (vm->m_stack_ptr == 0)
	{
		throw std::runtime_error("Stack underflow");
	}
	--vm->m_stack_ptr;
	obj = vm->m_stack[vm->m_stack_ptr];
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

void Instructions::CallSub(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command CALLSUB");
	}

	if (vm->m_jumpositions.count(params[1]) == 0)
	{
		throw std::runtime_error(std::string("No such label as") + params[1]);
	}

	int oldFP = vm->m_frame_ptr;
	int oldIP = vm->m_instructionPointer;

	vm->m_frame_ptr = vm->m_stack_ptr;
	vm->m_instructionPointer = vm->m_jumpositions[params[1]];


	VMObject obj;
	obj.type = ObjectType::INTEGER;

	obj.values.integer_value = oldFP;
	PushHelper(vm, obj);

	obj.values.integer_value = oldIP;
	PushHelper(vm, obj);
}

void Instructions::Ret(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command RET");
	}

	int paramPops = std::stoi(params[1]);

	VMObject framePtr = vm->m_stack[vm->m_frame_ptr];
	VMObject instructionPtr = vm->m_stack[vm->m_frame_ptr + 1];

	vm->m_stack_ptr -= (2 + paramPops); // remove instruction & frame pointers; remove any parameters from stack

	vm->m_frame_ptr = framePtr.values.integer_value;
	vm->m_instructionPointer = instructionPtr.values.integer_value;
}

void Instructions::Jump(VM * vm, const std::vector<std::string> &params)
{
	if (vm->m_jumpositions.count(params[1]) == 0)
	{
		throw std::runtime_error(std::string("No such label as ") + params[1]);
	}
	vm->m_instructionPointer = vm->m_jumpositions[params[1]];
}

void Instructions::JumpNotEqual(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command JNE");
	}

	if (vm->m_cmpResult != CmpResult::NO_RESULT && vm->m_cmpResult != CmpResult::EQUAL)
	{
		Jump(vm, params);
	}
}

void Instructions::JumpIfEqual(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command JEQ");
	}

	if (vm->m_cmpResult != CmpResult::NO_RESULT && vm->m_cmpResult == CmpResult::EQUAL)
	{
		Jump(vm, params);
	}
}

void Instructions::JumpIfLess(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command JLE");
	}

	if (vm->m_cmpResult != CmpResult::NO_RESULT && vm->m_cmpResult == CmpResult::LESSER)
	{
		Jump(vm, params);
	}
}

void Instructions::JumpIfGreater(VM * vm, const std::vector<std::string> &params)
{
	if (params.size() != 2)
	{
		throw std::runtime_error("Invalid parameter count for command JGR");
	}

	if (vm->m_cmpResult != CmpResult::NO_RESULT && vm->m_cmpResult == CmpResult::GREATER)
	{
		Jump(vm, params);
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

	int pos = vm->m_frame_ptr + offset;
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

	int pos = vm->m_frame_ptr + offset;
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

