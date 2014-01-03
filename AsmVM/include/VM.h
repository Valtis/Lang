#pragma once

#include <vector>
#include <string>
#include <array>
#include <stack>
#include <unordered_map>
#include <random>
#include "MemoryManager.h"

#include "VmObject.h"
#define REGISTER_CNT 16
#define STACK_SIZE 2048
class Instructions;

enum CmpResult {NO_RESULT, LESSER, EQUAL, GREATER };


class VM
{
public:
	VM();
	~VM();

	void Run(std::string file);


	void Push(VMObject &o);

	VMObject Pop();


	typedef std::vector<std::string> &InstrParam;
	void ExtractJumpPositions(std::vector<std::vector<std::string>> &tokens);
	
	std::unordered_map<std::string, int> m_jumpositions;
	
	std::array<VMObject, REGISTER_CNT> m_registers;
	std::array<VMObject, 1024> m_stack;

	int m_stack_ptr; // points to a next free stack spot
	int m_instruction_ptr;
	int m_frame_ptr;
	CmpResult m_cmpResult;
	
	MemoryManager m_memoryManager;

	std::mt19937 m_generator;

	bool m_endExecution;
};

