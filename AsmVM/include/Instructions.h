#pragma once
#include <vector>
#include <string>

class VM;

class Instructions
{
public:

	static void I_Add(VM * vm, const std::vector<std::string> &params);

	static void I_Sub(VM * vm, const std::vector<std::string> &params);

	static void I_Mov(VM *vm, const std::vector<std::string> &params);

	static void Print(VM * vm, const std::vector<std::string> &params);

	static void I_Alloc(VM * vm, const std::vector<std::string> &params);

	static void GC(VM * vm, const std::vector<std::string> &params);

	static void Push(VM * vm, const std::vector<std::string> &params);
	
	static void Pop(VM * vm, const std::vector<std::string> &params);



private:
	static int GetRegisterNumber(std::string, bool throwOnInvalid = true);
};