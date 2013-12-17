#include "VM.h"
#include "FileTokenizer.h"
#include "Instructions.h"
#include "Tokens.h"
#include <cstdio>
#include <fstream>



using namespace std;

VM::VM() : m_stack_ptr(0), m_frame_ptr(0), m_cmpResult(NO_RESULT)
{

	m_instructionHandlers["i_add"] = Instructions::I_Add;
	m_instructionHandlers["i_sub"] = Instructions::I_Sub;
	m_instructionHandlers["i_mul"] = Instructions::I_Mul;
	m_instructionHandlers["i_mov"] = Instructions::I_Mov;
	m_instructionHandlers["i_cmp"] = Instructions::I_Cmp;

	m_instructionHandlers["print"] = Instructions::Print;
	
	m_instructionHandlers["push"] = Instructions::Push;
	m_instructionHandlers["pop"] = Instructions::Pop;
	m_instructionHandlers["stackr"] = Instructions::StackRead;
	m_instructionHandlers["stackw"] = Instructions::StackWrite;


	m_instructionHandlers["callsub"] = Instructions::CallSub;
	m_instructionHandlers["ret"] = Instructions::Ret;
	m_instructionHandlers["jump"] = Instructions::Jump;
	m_instructionHandlers["jne"] = Instructions::JumpNotEqual;
	m_instructionHandlers["jeq"] = Instructions::JumpIfEqual;
	m_instructionHandlers["jle"] = Instructions::JumpIfLess;
	m_instructionHandlers["jgr"] = Instructions::JumpIfGreater;

	m_instructionHandlers["gc"] = Instructions::GC;
	m_instructionHandlers["print_mem_mgr_debug"] = Instructions::MemManagerDebugPrint;

	m_instructionHandlers["i_alloc"] = Instructions::I_Alloc;
	m_instructionHandlers["ipr"] = Instructions::I_ptr_read;
	m_instructionHandlers["ipw"] = Instructions::I_ptr_write;

}


VM::~VM()
{
}


void VM::Run(std::string fileName)
{
	ifstream file(fileName);
	std::vector<std::vector<std::string>> tokens = FileTokenizer::Tokenize(file);


	ExtractJumpPositions(tokens);
	

	while (m_instructionPointer < tokens.size())
	{
		if (tokens[m_instructionPointer][0] == END_TOKEN)
		{
			return;
		}

		if (m_instructionHandlers.count(tokens[m_instructionPointer][0]) == 0)
		{
			printf("Unrecognized command: %s", tokens[m_instructionPointer][0].c_str());
			return;
		}

		try
		{
			m_instructionHandlers[tokens[m_instructionPointer][0]](this, tokens[m_instructionPointer]);
			if (m_memoryManager.MustCollect())
			{
				m_memoryManager.RunGC(this);
			}

		}
		catch (const std::exception &ex)
		{
			printf(ex.what());
			return;
		}

		++m_instructionPointer;
	}
}

void VM::ExtractJumpPositions(std::vector<std::vector<std::string>> &tokens)
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
