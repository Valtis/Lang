#pragma once

#include <vector>
#include <string>
#include <array>
#include <stack>
#include <unordered_map>
#include <functional>
#include "MemoryManager.h"

#include "VmObject.h"
#define REGISTER_CNT 16
#define STACK_SIZE 1024
class Instructions;

class VM
{
public:
	VM();
	~VM();

	void Run(std::string file);
private:
	friend class Instructions;
	friend class MemoryManager;
	typedef std::vector<std::string> &InstrParam;
	
	std::unordered_map < std::string, std::function <void(VM *, InstrParam)>> m_instructionHandlers;
	
	std::array<VMObject, REGISTER_CNT> m_registers;
	std::array<VMObject, 1024> m_stack;
	int m_stack_ptr; // points to a next free stack spot

	int m_frame_ptr;
	
	MemoryManager m_memoryManager;
};

