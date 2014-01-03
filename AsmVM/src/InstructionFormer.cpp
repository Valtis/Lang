#include "InstructionFormer.h"
#include "Tokens.h"
#include "Instructions/Operand.h"

#include "Instructions/ArithmeticOperations.h"
#include "Instructions/JumpCommands.h"
// todo - replace runtime_errors with ParseExceptions and improve error messages
using namespace std;

int ParseRegister(string value)
{
	if (value[0] != REGISTER_START_TOKEN)
	{
		throw runtime_error("Source is not a register");
	}

	return value[1] - '0';
}

void SetIntegerOperand(Operand<int> &operand, const string &value)
{
	if (value[0] == REGISTER_START_TOKEN)
	{
		operand.SetRegister(value[1] - '0');
	}
	else
	{
		try		
		{
			operand.SetValue(stoi(value));
		}
		catch (const exception &ex)
		{
			throw runtime_error("Invalid operand given");
		}
	}
}

template <typename T>
unique_ptr<Instruction> ConstructIntegerOperation(vector<string> tokens)
{
	
	if (tokens.size() != 4)
	{
		throw runtime_error("Invalid parameter count for operation " + tokens[0]);
	}
	Operand<int> o1, o2;
	SetIntegerOperand(o1, tokens[1]);
	SetIntegerOperand(o2, tokens[2]);
	
	return unique_ptr<Instruction>(new T(o1, o2, ParseRegister(tokens[3])));
}

template <typename T>
unique_ptr<Instruction> ConstructJumpCommand(vector<string> tokens)
{
	if (tokens.size() != 2)
	{
		runtime_error("Invalid parameter count for operation " + tokens[0]);
	}
	return unique_ptr<Instruction>(new T(tokens[1]));
}


vector<unique_ptr<Instruction>> InstructionFormer::FormInstructions(const vector<vector<string>> &tokenizedLines)
{
	vector <unique_ptr<Instruction>> instructions;
	for (auto &tokens : tokenizedLines)
	{

		// todo: make this less shitty
		if (tokens[0] == INTEGER_ADDITION) 
		{
			instructions.push_back(ConstructIntegerOperation<Addition<int>>(tokens));
		}
		else if (tokens[0] == INTEGER_SUBSTRACTION)
		{
			instructions.push_back(ConstructIntegerOperation<Substraction<int>>(tokens));
		}
		else if (tokens[0] == INTEGER_MULTIPLICATION)
		{
			instructions.push_back(ConstructIntegerOperation<Multiplication<int>>(tokens));
		}
		else if (tokens[0] == INTEGER_DIVISION)
		{
			instructions.push_back(ConstructIntegerOperation<Division<int>>(tokens));
		}
		else if (tokens[0] == JUMP)
		{
			instructions.push_back(ConstructJumpCommand<Jump>(tokens));
		}
		else if (tokens[0] == JUMP_IF_EQUAL)
		{
			instructions.push_back(ConstructJumpCommand<JumpIfEqual>(tokens));
		}
		else if (tokens[0] == JUMP_NOT_EQUAL)
		{
			instructions.push_back(ConstructJumpCommand<JumpNotEqual>(tokens));
		}
		else if (tokens[0] == JUMP_IF_GREATER)
		{
			instructions.push_back(ConstructJumpCommand<JumpIfGreater>(tokens));
		}
		else if (tokens[0] == JUMP_IF_LESSER)
		{
			instructions.push_back(ConstructJumpCommand<JumpIfLess>(tokens));
		}
		else if (tokens[0] == INTEGER_RANDOMIZE)
		{
			instructions.push_back(ConstructIntegerOperation<RandomizeInteger>(tokens));
		}
		else 
		{
			throw runtime_error(std::string("unrecognized command: ") + tokens[0]);
		}
	
	}
	return instructions;
}
