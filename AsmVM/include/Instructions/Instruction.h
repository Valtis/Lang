#pragma once

class VM;

class Instruction
{
public:
	Instruction() { }
	virtual ~Instruction() { }
	
	virtual void Execute(VM *vm) = 0;
};