#pragma once
#include <vector>
#include <string>
#include <memory>
class Instruction;
namespace InstructionFormer
{
	std::vector<std::unique_ptr<Instruction>> FormInstructions(const std::vector<std::vector<std::string>> &tokenizedLines);
}