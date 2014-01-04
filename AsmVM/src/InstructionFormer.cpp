#include "InstructionFormer.h"
#include "Tokens.h"
#include "Instructions/Operand.h"

#include "Instructions/ArithmeticOperations.h"
#include "Instructions/JumpCommands.h"
#include "Instructions/RegisterManipulationOperations.h"
#include "Instructions/Print.h"
#include "Instructions/StackOperations.h"
#include "Instructions/UtilityInstructions.h"
#include "Instructions/IntegerPointerOperations.h"
// todo - replace runtime_errors with ParseExceptions and improve error messages
using namespace std;

int ParseRegister(const string &value)
{
	if (value[0] != REGISTER_START_TOKEN)
	{
		throw runtime_error("Source is not a register");
	}

	return stoi(value.substr(1, value.length() - 1));
}

void CheckParameterCount(vector<string> &tokens, int expected)
{
	if (tokens.size() != expected)
	{
		throw runtime_error("Invalid parameter count for operation " + tokens[0]);
	}
}

void SetIntegerOperand(Operand<int> &operand, const string &value)
{
	if (value[0] == REGISTER_START_TOKEN)
	{
		operand.SetRegister(ParseRegister(value));
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
unique_ptr<Instruction> ConstructIntegerOperation(vector<string> &tokens)
{
	CheckParameterCount(tokens, 4);
	
	Operand<int> o1, o2;
	SetIntegerOperand(o1, tokens[1]);
	SetIntegerOperand(o2, tokens[2]);
	
	return unique_ptr<Instruction>(new T(o1, o2, ParseRegister(tokens[3])));
}

unique_ptr<Instruction> ConstructIntegerCompareInstruction(vector<string> &tokens)
{
	CheckParameterCount(tokens, 3);

	Operand<int> o1, o2;

	SetIntegerOperand(o1, tokens[1]);
	SetIntegerOperand(o2, tokens[2]);


	return unique_ptr<Instruction>(new Compare<int>(o1, o2));
}

unique_ptr<Instruction> ConstructIntegerMoveInstruction(vector<string> &tokens)
{
	CheckParameterCount(tokens, 3);

	Operand<int> o1;
	SetIntegerOperand(o1, tokens[1]);
	
	return unique_ptr<Instruction>(new Move<int>(o1, ParseRegister(tokens[2])));
}

template <typename T>
unique_ptr<Instruction> ConstructJumpInstruction(vector<string> &tokens, unordered_map<string, int> &jumpPositions)
{
	CheckParameterCount(tokens, 2);
	if (jumpPositions.count(tokens[1]) == 0)
	{
		throw runtime_error("No label found: " + tokens[1]);
	}
	return unique_ptr<Instruction>(new T(jumpPositions[tokens[1]]));
}

unique_ptr<Instruction> ConstructReturnInstruction(vector<string> &tokens)
{
	CheckParameterCount(tokens, 2);

	return unique_ptr<Instruction>(new Ret(stoi(tokens[1])));
}

unique_ptr<Instruction> ConstructPrintInstruction(vector<string> &tokens)
{
	if (tokens.size() <= 1)
	{
		throw runtime_error("Invalid parameter count for operation " + tokens[0]);
	}

	if (tokens[1][0] == PRINT_TEXT_TOKEN)
	{
		return unique_ptr<Instruction>(new Print(tokens));
	}

	return unique_ptr<Instruction>(new Print(ParseRegister(tokens[1])));
}

unique_ptr<Instruction> ConstructPushInstruction(vector<string> &tokens)
{
	CheckParameterCount(tokens, 2);

	if (tokens[1] == NIL_TOKEN)
	{
		return unique_ptr<Instruction>(new Push(-1));
	}

	return unique_ptr<Instruction>(new Push(ParseRegister(tokens[1])));
}

unique_ptr<Instruction> ConstructPopInstruction(vector<string> &tokens)
{
	CheckParameterCount(tokens, 2);

	return unique_ptr<Instruction>(new Pop(ParseRegister(tokens[1])));
}

template <typename T>
unique_ptr<Instruction> ConstructStackOperation(vector<string> &tokens)
{
	CheckParameterCount(tokens, 3);
	
	Operand<int> o1;
	SetIntegerOperand(o1, tokens[1]);
	
	return unique_ptr<Instruction>(new T(o1, ParseRegister(tokens[2])));
}


template <typename T>
unique_ptr<Instruction> ConstructParameterlessInstruction()
{
	
	return unique_ptr<Instruction>(new T);
}

unique_ptr<Instruction> ConstructIntegerAllocationInstruction(vector<string> &tokens)
{
	CheckParameterCount(tokens, 3);
	
	Operand<int> o1;
	SetIntegerOperand(o1, tokens[1]);

	return unique_ptr<Instruction>(new AllocateIntegerPointer(o1, ParseRegister(tokens[2])));
}

unique_ptr<Instruction> WriteToIntegerPtr(vector<string> &tokens)
{
	CheckParameterCount(tokens, 4);

	Operand<int> value;
	Operand<int> location;

	SetIntegerOperand(value, tokens[1]);
	SetIntegerOperand(location, tokens[2]);

	return unique_ptr<Instruction>(new WriteToIntegerPointer(value, location, ParseRegister(tokens[3])));
}

unique_ptr<Instruction> ReadFromIntegerPtr(vector<string> &tokens)
{
	CheckParameterCount(tokens, 4);

	Operand<int> location;
	SetIntegerOperand(location, tokens[2]);

	return unique_ptr<Instruction>(new ReadFromIntegerPointer(ParseRegister(tokens[1]), location, ParseRegister(tokens[3])));
}

vector<unique_ptr<Instruction>> InstructionFormer::FormInstructions(vector<vector<string>> &tokenizedLines)
{
	auto jumpPositions = InstructionFormer::ExtractJumpPositions(tokenizedLines);

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
		else if (tokens[0] == INTEGER_RANDOMIZE)
		{
			instructions.push_back(ConstructIntegerOperation<RandomizeInteger>(tokens));
		}
		else if (tokens[0] == INTEGER_COMPARE)
		{
			instructions.push_back(ConstructIntegerCompareInstruction(tokens));
		}
		else if (tokens[0] == INTEGER_MOVE)
		{
			instructions.push_back(ConstructIntegerMoveInstruction(tokens));
		}
		else if (tokens[0] == JUMP)
		{
			instructions.push_back(ConstructJumpInstruction<Jump>(tokens, jumpPositions));
		}
		else if (tokens[0] == JUMP_IF_EQUAL)
		{
			instructions.push_back(ConstructJumpInstruction<JumpIfEqual>(tokens, jumpPositions));
		}
		else if (tokens[0] == JUMP_NOT_EQUAL)
		{
			instructions.push_back(ConstructJumpInstruction<JumpNotEqual>(tokens, jumpPositions));
		}
		else if (tokens[0] == JUMP_IF_GREATER)
		{
			instructions.push_back(ConstructJumpInstruction<JumpIfGreater>(tokens, jumpPositions));
		}
		else if (tokens[0] == JUMP_IF_LESSER)
		{
			instructions.push_back(ConstructJumpInstruction<JumpIfLess>(tokens, jumpPositions));
		}
		else if (tokens[0] == CALLSUB)
		{
			instructions.push_back(ConstructJumpInstruction<CallSub>(tokens, jumpPositions));
		}
		else if (tokens[0] == RET)
		{
			instructions.push_back(ConstructReturnInstruction(tokens));
		}
		else if (tokens[0] == PRINT)
		{
			instructions.push_back(ConstructPrintInstruction(tokens));
		}
		else if (tokens[0] == PUSH)
		{
			instructions.push_back(ConstructPushInstruction(tokens));
		}
		else if (tokens[0] == POP)
		{
			instructions.push_back(ConstructPopInstruction(tokens));
		}
		else if (tokens[0] == STACK_READ)
		{
			instructions.push_back(ConstructStackOperation<ReadStack>(tokens));
		}
		else if (tokens[0] == STACK_WRITE)
		{
			instructions.push_back(ConstructStackOperation<WriteStack>(tokens));
		}
		else if (tokens[0] == ALLOCATE_INTEGER_POINTER)
		{
			instructions.push_back(ConstructIntegerAllocationInstruction(tokens));
		}
		else if (tokens[0] == WRITE_TO_INTEGER_POINTER)
		{
			instructions.push_back(WriteToIntegerPtr(tokens));
		}
		else if (tokens[0] == READ_FROM_INTEGER_POINTER)
		{
			instructions.push_back(ReadFromIntegerPtr(tokens));
		}
		else if (tokens[0] == END)
		{
			instructions.push_back(ConstructParameterlessInstruction<End>());
		}
		else if (tokens[0] == FORCE_GC)
		{
			instructions.push_back(ConstructParameterlessInstruction<GC>());
		}
		else if (tokens[0] == MEMORY_MANAGER_DEBUG_STATE)
		{
			instructions.push_back(ConstructParameterlessInstruction<MemoryManagedPrintState>());
		}
		else 
		{
			throw runtime_error(std::string("unrecognized command: ") + tokens[0]);
		}
	
	}
	return instructions;
}


unordered_map<string, int> InstructionFormer::ExtractJumpPositions(vector<vector<string>> &tokens)
{
	unordered_map<string, int> jumPositions;
	int pos = 0;
	auto it = tokens.begin();
	while (it != tokens.end())
	{
		int endPos = (*it)[0].length() - 1;
		if ((*it)[0][endPos] == ':')
		{
			auto label = (*it)[0].substr(0, endPos);
			// instruction pointer is incremented after jump instruction
			// therefore the actual jump position needs to be one before the instruction we jump to
			jumPositions[label] = pos - 1;
			it = tokens.erase(it);
			continue;
		}

		++pos;
		++it;
	}
	return jumPositions;
}