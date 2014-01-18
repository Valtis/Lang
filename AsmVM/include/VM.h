#pragma once

#include <vector>
#include <string>
#include <array>
#include <stack>
#include <unordered_map>
#include <memory>
#include <random>
#include "MemoryManager.h"

#include "VmObject.h"
#define REGISTER_CNT 16
#define STACK_SIZE 2048
class Instruction;

enum CmpResult { NO_RESULT, LESSER, EQUAL, GREATER };


class VM
{
public:
	VM();
	~VM();

	void Run(std::string file);

	void ExecuteProgram(std::vector<std::unique_ptr<Instruction>> &instructions, long int &instructionsPerformed, std::vector<std::vector<std::string>> tokens);

	void PrintError(const std::vector<std::vector<std::string>> &tokens, const std::exception &ex);

	void HandleGarbageCollection();

	void ParseFile(const std::string &fileName, std::vector<std::vector<std::string>> &tokens, std::vector<std::unique_ptr<Instruction>> &instructions);

	void Push(VMObject &o);
	VMObject Pop();

		
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

