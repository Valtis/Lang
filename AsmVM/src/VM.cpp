#include "VM.h"
#include "FileTokenizer.h"
#include "Instructions/Instruction.h"
#include "InstructionFormer.h"
#include "Tokens.h"
#include <cstdio>
#include <fstream>
#include <ctime>
#include <memory>
#include <chrono>
using namespace std;

VM::VM() : m_stack_ptr(0), m_instruction_ptr(0), m_frame_ptr(0), m_cmpResult(NO_RESULT), m_endExecution(false)
{
	m_generator.seed(time(nullptr));

}


VM::~VM()
{
}


void VM::Run(string fileName)
{
	vector<vector<string>> tokens;
	vector<unique_ptr<Instruction>> instructions;
	ParseFile(fileName, tokens, instructions);
	
	if (instructions.empty())
	{
		return;
	}

	long int instructionsPerformed = 0;
	auto start = chrono::system_clock::now();
	
	ExecuteProgram(instructions, instructionsPerformed, tokens);
	
	auto end = chrono::system_clock::now();
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
	printf("Performed %d instructions in %ld millisecond", instructionsPerformed, milliseconds.count());
}

void VM::ParseFile(const string &fileName, vector<vector<string>> &tokens, vector<unique_ptr<Instruction>> &instructions)
{
	ifstream file(fileName);
	tokens = FileTokenizer::Tokenize(file);

	try
	{
		instructions = InstructionFormer::FormInstructions(tokens);
	}
	catch (const exception &ex)
	{
		printf("Parse error: %s", ex.what());
		return;
	}
}


void VM::ExecuteProgram(vector<unique_ptr<Instruction>> &instructions, long int &instructionsPerformed, vector<vector<string>> tokens)
{
	while (m_instruction_ptr < instructions.size() && m_endExecution == false)
	{
		try
		{
			instructions[m_instruction_ptr]->Execute(this);
			HandleGarbageCollection();
			++instructionsPerformed;
		}
		catch (const exception &ex)
		{
			PrintError(tokens, ex);
			return;
		}

		++m_instruction_ptr;
	}
}


inline void VM::HandleGarbageCollection()
{
	if (m_memoryManager.MustCollect())
	{
		m_memoryManager.RunGC(this);
	}
}

void VM::PrintError(const vector<vector<string>> &tokens, const exception &ex)
{
	string error = "";
	for (auto str : tokens[m_instruction_ptr])
	{
		error += str + " ";
	}

	printf("Error on command %s\n", error.c_str());
	printf("Error: %s\n", ex.what());
}



void VM::Push(VMObject &obj)
{
	if (m_stack_ptr >= STACK_SIZE)
	{
		throw std::runtime_error("Stack overflow");
	}
	m_stack[m_stack_ptr++] = obj;

}

VMObject VM::Pop()
{
	if (m_stack_ptr == 0)
	{
		throw std::runtime_error("Stack underflow");
	}
	--m_stack_ptr;
	return m_stack[m_stack_ptr];
}
