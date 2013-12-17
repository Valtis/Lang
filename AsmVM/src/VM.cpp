#include "VM.h"
#include "FileTokenizer.h"
#include "Instructions.h"
#include <cstdio>
#include <fstream>


using namespace std;

VM::VM() : m_stack_ptr(0), m_frame_ptr(0)
{

	m_instructionHandlers["i_add"] = Instructions::I_Add;
	m_instructionHandlers["i_sub"] = Instructions::I_Sub;
	m_instructionHandlers["i_mov"] = Instructions::I_Mov;

	m_instructionHandlers["print"] = Instructions::Print;

	m_instructionHandlers["gc"] = Instructions::GC;
	m_instructionHandlers["i_alloc"] = Instructions::I_Alloc;


}


VM::~VM()
{
}


void VM::Run(std::string fileName)
{
	ifstream file(fileName);
	FileTokenizer::TokenizedLines tokens = FileTokenizer::Tokenize(file);

	for (auto lineTokens : tokens)
	{
		if (m_instructionHandlers.count(lineTokens[0]) == 0)
		{
			printf("Unrecognized command: %s", lineTokens[0].c_str());
			return;
		}

		try
		{
			m_instructionHandlers[lineTokens[0]](this, lineTokens);
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
	}
}