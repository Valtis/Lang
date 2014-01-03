#pragma once
#include "Instructions/Instruction.h"
#include "Vm.h"
#include <string>

class Jump : public Instruction
{
public:
	Jump(const std::string &label) : m_label(label)
	{
		
	}

	virtual ~Jump() { }

	std::string GetLabel()
	{
		return m_label;
	}

	virtual void Execute(VM *vm) override
	{
		if (vm->m_jumpositions.count(m_label) == 0)
		{
			throw std::runtime_error(std::string("Invalid label ") + m_label);
		}
		OnExecute(vm);
	}

protected:
	virtual void OnExecute(VM *vm)
	{
		vm->m_instructionPointer = vm->m_jumpositions[m_label];
	}

private:
	std::string m_label;
};

class JumpNotEqual : public Jump
{
public:
	JumpNotEqual(const std::string &label) : Jump(label)
	{

	}
private:
	void OnExecute(VM *vm) override
	{
		if (vm->m_cmpResult != CmpResult::NO_RESULT && vm->m_cmpResult != CmpResult::EQUAL)
		{
			Jump::OnExecute(vm);
		}
	}
};

class JumpIfEqual : public Jump
{
public:
	JumpIfEqual(const std::string &label) : Jump(label)
	{

	}
private:
	void OnExecute(VM *vm) override
	{
		if (vm->m_cmpResult != CmpResult::NO_RESULT && vm->m_cmpResult == CmpResult::EQUAL)
		{
			Jump::OnExecute(vm);
		}
	}
};

class JumpIfLess : public Jump
{
public:
	JumpIfLess(const std::string &label) : Jump(label)
	{

	}
private:
	void OnExecute(VM *vm) override
	{
		if (vm->m_cmpResult != CmpResult::NO_RESULT && vm->m_cmpResult == CmpResult::LESSER)
		{
			Jump::OnExecute(vm);
		}
	}
};


class JumpIfGreater : public Jump
{
public:
	JumpIfGreater(const std::string &label) : Jump(label)
	{

	}
private:
	void OnExecute(VM *vm) override
	{
		if (vm->m_cmpResult != CmpResult::NO_RESULT && vm->m_cmpResult == CmpResult::GREATER)
		{
			Jump::OnExecute(vm);
		}
	}
};

class CallSub : public Jump
{
public:
	CallSub(const std::string &label) : Jump(label)
	{

	}
private:
	void OnExecute(VM *vm) override
	{

		int oldFP = vm->m_frame_ptr;
		int oldIP = vm->m_instructionPointer;

		VMObject o;
		o.type = ObjectType::INTEGER;
		o.values.integer_value = oldFP;

		vm->Push(o);

		o.values.integer_value = oldIP;
		vm->Push(o);


		vm->m_frame_ptr = vm->m_stack_ptr;

		Jump::OnExecute(vm);
	}


};


/*

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
}*/
