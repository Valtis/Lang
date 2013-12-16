#pragma once
#include <vector>
#include <string>
class VM;

class Commands
{
public:
	static void I_Add(VM * vm, const std::vector<std::string> &params);

	static void I_Mov(VM *vm, const std::vector<std::string> &params);

	static void Print(VM * vm, const std::vector<std::string> &params);
private:
	static int GetRegisterNumber(std::string, bool throwOnInvalid = true);
};