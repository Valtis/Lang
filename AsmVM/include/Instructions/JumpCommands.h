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