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
	ifstream file(fileName);
	vector<vector<string>> tokens = FileTokenizer::Tokenize(file);

	
	ExtractJumpPositions(tokens);
	vector<std::unique_ptr<Instruction>> instructions;
	try 
	{
		instructions = InstructionFormer::FormInstructions(tokens);
	} 
	catch (const exception &ex)
	{
		printf("Parse error: %s", ex.what());
		return;
	}
	
	int instructionsPerformed = 0;

	auto start = chrono::system_clock::now();
	while (m_instruction_ptr < instructions.size() && m_endExecution == false)
	{
		try
		{
			instructions[m_instruction_ptr]->Execute(this);
			if (m_memoryManager.MustCollect())
			{
				m_memoryManager.RunGC(this);
			}
			++instructionsPerformed;

		}
		catch (const exception &ex)
		{
			printf("Error: %s\n", ex.what());
			return;
		}

		++m_instruction_ptr;
	}

	auto end = chrono::system_clock::now();

	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
	
	printf("Performed %d instructions in %d millisecond", instructionsPerformed, milliseconds.count());

}

void VM::ExtractJumpPositions(vector<vector<string>> &tokens)
{
	int pos = 0;
	auto it = tokens.begin();
	while (it != tokens.end())
	{
		int endPos = (*it)[0].length() - 1;
		if ((*it)[0][endPos] == ':')
		{
			auto label = (*it)[0].substr(0, endPos);
			m_jumpositions[label] = pos-1;
			it = tokens.erase(it);
			continue;
		}

		++pos;
		++it;
	}
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
