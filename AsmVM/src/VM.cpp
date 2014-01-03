#include "VM.h"
#include "FileTokenizer.h"
#include "Instructions/Instruction.h"
#include "InstructionFormer.h"
#include "Tokens.h"
#include <cstdio>
#include <fstream>
#include <ctime>
#include <memory>

using namespace std;

VM::VM() : m_stack_ptr(0), m_frame_ptr(0), m_cmpResult(NO_RESULT), m_endExecution(false)
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
	vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(tokens);
	
	

	while (m_instructionPointer < instructions.size() && m_endExecution == false)
	{
		try
		{
			instructions[m_instructionPointer]->Execute(this);
			if (m_memoryManager.MustCollect())
			{
				m_memoryManager.RunGC(this);
			}

		}
		catch (const exception &ex)
		{
			printf("Error: %s\n", ex.what());
			return;
		}

		++m_instructionPointer;
	}
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
