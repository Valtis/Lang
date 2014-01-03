#include "stdafx.h"
#include "CppUnitTest.h"
#include "Instructions/IntegerPointerOperations.h"
#include "VM.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(IntegerPointerOperationsTest)
	{
	public:

		TEST_METHOD(AllocateIntegerPointerAllocatesCorrectTypeWithValueOperand)
		{
			const int destRegister = 6;
			const int size = 200;

			VM vm;

			Operand<int> op;
			op.SetValue(size);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Assert::AreEqual((int)ObjectType::INTEGER_PTR, (int)vm.m_registers[destRegister].type);
		}

		TEST_METHOD(AllocateIntegerPointerAllocatesCorrectAmountWithValueOperand)
		{
			const int destRegister = 6;
			const int size = 200;

			VM vm;

			Operand<int> op;
			op.SetValue(size);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Assert::AreEqual(size*4, vm.m_registers[destRegister].values.ptr->size);
		}

		TEST_METHOD(AllocateIntegerPointerAllocatesCorrectTypeWithRegisterOperand)
		{
			const int srcRegister = 2;
			const int destRegister = 6;
			const int size = 200;

			VM vm;
			vm.m_registers[srcRegister].values.integer_value = size;

			Operand<int> op;
			op.SetRegister(srcRegister);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Assert::AreEqual((int)ObjectType::INTEGER_PTR, (int)vm.m_registers[destRegister].type);
		}

		TEST_METHOD(AllocateIntegerPointerAllocatesCorrectAmountWithRegisterOperand)
		{
			const int srcRegister = 2;
			const int destRegister = 6;
			const int size = 200;

			VM vm;
			vm.m_registers[srcRegister].values.integer_value = size;

			Operand<int> op;
			op.SetRegister(srcRegister);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Assert::AreEqual(size*4, vm.m_registers[destRegister].values.ptr->size);
		}
	};
}