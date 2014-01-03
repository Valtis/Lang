#include "InstructionFormer.h"
#include "Tokens.h"
#include "Instructions/Operand.h"

#include "Instructions/ArithmeticOperations.h"

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


void IntegerOperationHelper(const vector<string> &tokens, Operand<int> &o1, Operand<int> &o2)
{
	if (tokens.size() != 4)
	{
		throw runtime_error("Invalid parameter count for operation " + tokens[0]);
	}
	SetIntegerOperand(o1, tokens[1]);
	SetIntegerOperand(o2, tokens[2]);
}


unique_ptr<Instruction> ConstructIntegerAddition(vector<string> tokens)
{
	Operand<int> o1, o2;
	IntegerOperationHelper(tokens, o1, o2);
	
	return unique_ptr<Instruction>(new Addition<int>(o1, o2, ParseRegister(tokens[3])));
}

unique_ptr<Instruction> ConstructIntegerSubstraction(vector<string> tokens)
{
	Operand<int> o1, o2;
	IntegerOperationHelper(tokens, o1, o2);

	return unique_ptr<Instruction>(new Substraction<int>(o1, o2, ParseRegister(tokens[3])));
}

unique_ptr<Instruction> ConstructIntegerMultiplication(vector<string> tokens)
{
	Operand<int> o1, o2;
	IntegerOperationHelper(tokens, o1, o2);

	return unique_ptr<Instruction>(new Multiplication<int>(o1, o2, ParseRegister(tokens[3])));
}

unique_ptr<Instruction> ConstructIntegerDivision(vector<string> tokens)
{
	Operand<int> o1, o2;
	IntegerOperationHelper(tokens, o1, o2);

	return unique_ptr<Instruction>(new Division<int>(o1, o2, ParseRegister(tokens[3])));
}


vector<unique_ptr<Instruction>> InstructionFormer::FormInstructions(const vector<vector<string>> &tokenizedLines)
{
	vector <unique_ptr<Instruction>> instructions;
	for (auto &token : tokenizedLines)
	{

		// todo: make this less shitty
		if (token[0] == INTEGER_ADDITION) 
		{
			instructions.push_back(ConstructIntegerAddition(token));
		}
		else if (token[0] == INTEGER_SUBSTRACTION)
		{
			instructions.push_back(ConstructIntegerSubstraction(token));
		}
		else if (token[0] == INTEGER_MULTIPLICATION)
		{
			instructions.push_back(ConstructIntegerMultiplication(token));
		}
		else if (token[0] == INTEGER_DIVISION)
		{
			instructions.push_back(ConstructIntegerDivision(token));
		}
		else {
			throw runtime_error(std::string("unrecognized command: ") + token[0]);
		}
	
	}
	return instructions;
}
