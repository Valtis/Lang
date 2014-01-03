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
		vm->m_instruction_ptr = vm->m_jumpositions[m_label];
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
		int oldIP = vm->m_instruction_ptr;
		vm->m_frame_ptr = vm->m_stack_ptr;

		VMObject o;
		o.type = ObjectType::INTEGER;
		o.values.integer_value = oldFP;


		vm->Push(o);

		o.values.integer_value = oldIP;
		vm->Push(o);

		Jump::OnExecute(vm);
	}


};

class Ret : public Instruction
{
public:
	Ret(int pops)
	{
		if (pops < 0)
		{
			throw std::runtime_error("Invalid pop count for return instruction");
		}

		m_pops = pops;

	}
	void Execute(VM *vm) override
	{
		VMObject framePtr = vm->m_stack[vm->m_frame_ptr];
		VMObject instructionPtr = vm->m_stack[vm->m_frame_ptr + 1];

		vm->m_stack_ptr -= (2 + m_pops); // remove instruction & frame pointers; remove any parameters from stack

		if (vm->m_stack_ptr < 0)
		{
			throw std::runtime_error("Negative stack pointer after returning from function call");
		}

		vm->m_frame_ptr = framePtr.values.integer_value;
		vm->m_instruction_ptr = instructionPtr.values.integer_value;
	}

private:
	int m_pops;

};


/*

void Instructions::Ret(VM * vm, const std::vector<std::string> &params)
{
	
}*/
