#pragma once
#include <vector>
#include <string>

class VM;
struct VMObject;
class Instructions
{
public:
	
	
	static void I_Alloc(VM * vm, const std::vector<std::string> &params);
	
	static void I_ptr_write(VM * vm, const std::vector<std::string> &params);
	
	static void I_ptr_read(VM * vm, const std::vector<std::string> &params);

	static void GC(VM * vm, const std::vector<std::string> &params);

	static void MemManagerDebugPrint(VM * vm, const std::vector<std::string> &params);


private:
	static int GetRegisterNumber(std::string, bool throwOnInvalid = true);
	static int I_ValueHelper(VM *vm, std::string param);
	static void ArithmeticOperationHelper(VM *vm, const std::vector<std::string> &params, int &destReg, int &val1, int &val2);
	static void PushHelper(VM *vm, VMObject &obj);
	static void PopHelper(VM *vm, VMObject &obj);
};