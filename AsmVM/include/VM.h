#pragma once

#include <vector>
#include <string>
#include <array>


#include "VmObject.h"
#define REGISTER_CNT 16

class VM
{
public:
	VM();
	~VM();

	void Run(std::string file);

private:
	std::array<VMObject, REGISTER_CNT> m_registers;
	Stack<VMObject> m_stack;
};

