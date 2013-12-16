#include "VM.h"
#include "FileTokenizer.h"
#include <fstream>
using namespace std;

VM::VM()
{
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

	}
}