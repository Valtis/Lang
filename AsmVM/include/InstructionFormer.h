#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
class Instruction;
namespace InstructionFormer
{
	std::unordered_map<std::string, int> ExtractJumpPositions(std::vector<std::vector<std::string>> &tokens);

	std::vector<std::unique_ptr<Instruction>> FormInstructions(std::vector<std::vector<std::string>> &tokenizedLines);
		
}