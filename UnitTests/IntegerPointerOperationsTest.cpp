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

		TEST_METHOD(WriteToIntegerPointerThrowsOnNegativeIndex)
		{
			const int destRegister = 6;
			const int size = 200;

			VM vm;

			Operand<int> op;
			op.SetValue(size);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Operand<int> value;
			value.SetValue(20);
			
			Operand<int> location;
			location.SetValue(-1);

			WriteToIntegerPointer write(value, location, destRegister);
			Assert::ExpectException<runtime_error>([&]() {write.Execute(&vm); });
		}

		TEST_METHOD(WriteToIntegerPointerThrowsOnTooLargeIndex)
		{
			const int destRegister = 6;
			const int size = 200;

			VM vm;

			Operand<int> op;
			op.SetValue(size);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Operand<int> value;
			value.SetValue(20);

			Operand<int> location;
			location.SetValue(200);

			WriteToIntegerPointer write(value, location, destRegister);
			Assert::ExpectException<runtime_error>([&]() {write.Execute(&vm); });
		}

		TEST_METHOD(WriteToIntegerPointerWritesCorrectly)
		{
			const int destRegister = 6;
			const int size = 200;

			VM vm;

			Operand<int> op;
			op.SetValue(size);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Operand<int> value;
			value.SetValue(20);

			Operand<int> location;
			location.SetValue(150);

			WriteToIntegerPointer write(value, location, destRegister);
			write.Execute(&vm);

			int *array = (int *)vm.m_registers[destRegister].values.ptr->ptr;
			Assert::AreEqual(20, array[150]);
		}

		TEST_METHOD(ReadFromIntegerPointerThrowsOnNegativeIndex)
		{
			const int destRegister = 6;
			const int size = 200;

			VM vm;

			Operand<int> op;
			op.SetValue(size);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Operand<int> value;
			value.SetValue(20);

			Operand<int> location;
			location.SetValue(-1);

			ReadFromIntegerPointer read(destRegister, location, 1);
			Assert::ExpectException<runtime_error>([&]() {read.Execute(&vm); });
		}

		TEST_METHOD(ReadFromIntegerPointerThrowsOnTooLargeIndex)
		{
			const int destRegister = 6;
			const int size = 200;

			VM vm;

			Operand<int> op;
			op.SetValue(size);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			Operand<int> value;
			value.SetValue(20);

			Operand<int> location;
			location.SetValue(200);

			ReadFromIntegerPointer read(destRegister, location, 5);
			Assert::ExpectException<runtime_error>([&]() { read.Execute(&vm); });
		}

		TEST_METHOD(ReadFromIntegerPointerReadsCorrectly)
		{
			const int destRegister = 6;
			const int size = 200;

			VM vm;

			Operand<int> op;
			op.SetValue(size);

			AllocateIntegerPointer allocate(op, destRegister);
			allocate.Execute(&vm);

			int *array = (int *)vm.m_registers[destRegister].values.ptr->ptr;
			for (int i = 0; i < 200; ++i)
			{
				array[i] = i;
			}

		

			Operand<int> value;
			value.SetValue(20);

			Operand<int> location;
			location.SetValue(150);

			ReadFromIntegerPointer read(destRegister, location, 1);
			read.Execute(&vm);

			
			Assert::AreEqual(150, vm.m_registers[1].values.integer_value);
		}

	};
}