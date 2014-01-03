#pragma once
#include <vector>
#include <string>

class VM;
struct VMObject;
class Instructions
{
public:

	/*static void I_Add(VM * vm, const std::vector<std::string> &params);

	static void I_Sub(VM * vm, const std::vector<std::string> &params);

	static void I_Mul(VM * vm, const std::vector<std::string> &params);

	static void I_Div(VM * vm, const std::vector<std::string> &params);
	*/
	static void I_Rand(VM *vm, const std::vector<std::string> &params);

	static void I_Cmp(VM * vm, const std::vector<std::string> &params);

	static void I_Mov(VM *vm, const std::vector<std::string> &params);

	static void Print(VM * vm, const std::vector<std::string> &params);

	static void I_Alloc(VM * vm, const std::vector<std::string> &params);
	
	static void I_ptr_write(VM * vm, const std::vector<std::string> &params);
	
	static void I_ptr_read(VM * vm, const std::vector<std::string> &params);

	static void GC(VM * vm, const std::vector<std::string> &params);

	static void MemManagerDebugPrint(VM * vm, const std::vector<std::string> &params);

	static void Push(VM * vm, const std::vector<std::string> &params);
	
	static void Pop(VM * vm, const std::vector<std::string> &params);

	static void StackRead(VM * vm, const std::vector<std::string> &params);
	
	static void StackWrite(VM * vm, const std::vector<std::string> &params);

	static void CallSub(VM * vm, const std::vector<std::string> &params);

	static void Ret(VM * vm, const std::vector<std::string> &params);

	static void Jump(VM * vm, const std::vector<std::string> &params);

	static void JumpNotEqual(VM * vm, const std::vector<std::string> &params);

	static void JumpIfEqual(VM * vm, const std::vector<std::string> &params);

	static void JumpIfLess(VM * vm, const std::vector<std::string> &params);

	static void JumpIfGreater(VM * vm, const std::vector<std::string> &params);


	

private:
	static int GetRegisterNumber(std::string, bool throwOnInvalid = true);
	static int I_ValueHelper(VM *vm, std::string param);
	static void ArithmeticOperationHelper(VM *vm, const std::vector<std::string> &params, int &destReg, int &val1, int &val2);
	static void PushHelper(VM *vm, VMObject &obj);
	static void PopHelper(VM *vm, VMObject &obj);
};