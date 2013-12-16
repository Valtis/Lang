#pragma once

#include <vector>
#include <string>
#include <array>
#include <stack>
#include <unordered_map>
#include <functional>

#include "VmObject.h"
#define REGISTER_CNT 16
class Commands;

class VM
{
public:
	VM();
	~VM();

	void Run(std::string file);
private:
	friend class Commands;
	typedef std::vector<std::string> &InstrParam;
	
	std::unordered_map < std::string, std::function <void(VM *, InstrParam)>> m_instructionHandlers;
	std::unordered_map<std::string, VMObject> m_variables;
	std::array<VMObject, REGISTER_CNT> m_registers;
	
	std::stack<VMObject> m_stack;
};

