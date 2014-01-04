#pragma once
#include "Instructions/Instruction.h"
#include "Vm.h"
#include <string>

class Jump : public Instruction
{
public:
	Jump(int instruction) : m_instruction(instruction)
	{
		
	}

	virtual ~Jump() { }

	
	virtual void Execute(VM *vm) override
	{
		OnExecute(vm);
	}

protected:
	virtual void OnExecute(VM *vm)
	{
		vm->m_instruction_ptr = m_instruction;
	}

private:
	int m_instruction;
};

class JumpNotEqual : public Jump
{
public:
	JumpNotEqual(int instruction) : Jump(instruction)
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
	JumpIfEqual(int instruction) : Jump(instruction)
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
	JumpIfLess(int instruction) : Jump(instruction)
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
	JumpIfGreater(int instruction) : Jump(instruction)
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
	CallSub(int instruction) : Jump(instruction)
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
