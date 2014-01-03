#pragma once
#include "Instructions/Instruction.h"
#include "VM.h"

class End : public Instruction
{
public:
	void Execute(VM *vm) override
	{
		vm->m_endExecution = true;
	}
};