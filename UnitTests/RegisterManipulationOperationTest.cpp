#include "stdafx.h"
#include "CppUnitTest.h"
#include "VM.h"
#include "Instructions/RegisterManipulationOperations.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(RegisterManipulationOperationTest)
	{
	public:

		TEST_METHOD(IntegerComparisonWorksWhenComparingLess)
		{
			VM vm;

			const int value1 = 5;
			const int value2 = 7;

			Operand<int> op1;
			Operand<int> op2;

			op1.SetValue(value1);
			op2.SetValue(value2);

			Compare<int> comp(op1, op2);

			comp.Execute(&vm);
			
			Assert::AreEqual((int)CmpResult::LESSER, (int)vm.m_cmpResult);
		}

		TEST_METHOD(IntegerComparisonWorksWhenComparingEqual)
		{
			VM vm;

			const int value1 = 20;
			const int value2 = 20;

			Operand<int> op1;
			Operand<int> op2;

			op1.SetValue(value1);
			op2.SetValue(value2);

			Compare<int> comp(op1, op2);

			comp.Execute(&vm);

			Assert::AreEqual((int)CmpResult::EQUAL, (int)vm.m_cmpResult);
		}

		TEST_METHOD(IntegerComparisonWorksWhenComparingGreater)
		{
			VM vm;

			const int value1 = 4352;
			const int value2 = 456;

			Operand<int> op1;
			Operand<int> op2;

			op1.SetValue(value1);
			op2.SetValue(value2);

			Compare<int> comp(op1, op2);

			comp.Execute(&vm);

			Assert::AreEqual((int)CmpResult::GREATER, (int)vm.m_cmpResult);
		}

		TEST_METHOD(IntegerMoveStoresRightTypeWhenMovingValue)
		{
			VM vm;
			const int destRegister = 5;
			const int value = 35;

			Operand<int> op1;
			op1.SetValue(value);

			Move<int> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual((int)ObjectType::INTEGER, (int)vm.m_registers[destRegister].type);
		}

		TEST_METHOD(IntegerMoveStoresRightValueWhenMovingValue)
		{
			VM vm;
			const int destRegister = 5;
			const int value = 35;

			Operand<int> op1;
			op1.SetValue(value);

			Move<int> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual(value, vm.m_registers[destRegister].values.integer_value);
		}

		TEST_METHOD(IntegerMoveStoresRightTypeWhenMovingRegister)
		{
			VM vm;
			const int destRegister = 5;
			const int srcRegister = 2;
			const int value = 35;

			vm.m_registers[srcRegister].values.integer_value = value;

			Operand<int> op1;
			op1.SetRegister(srcRegister);

			Move<int> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual((int)ObjectType::INTEGER, (int)vm.m_registers[destRegister].type);
		}

		TEST_METHOD(IntegerMoveStoresRightValueWhenMovingRegister)
		{
			VM vm;
			const int destRegister = 5;
			const int srcRegister = 2;
			const int value = 35;

			vm.m_registers[srcRegister].values.integer_value = value;

			Operand<int> op1;
			op1.SetRegister(srcRegister);

			Move<int> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual(value, vm.m_registers[destRegister].values.integer_value);
		}

		TEST_METHOD(DoubleMoveStoresRightTypeWhenMovingValue)
		{
			VM vm;
			const int destRegister = 5;
			const double value = 359.254;

			Operand<double> op1;
			op1.SetValue(value);

			Move<double> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual((int)ObjectType::DOUBLE, (int)vm.m_registers[destRegister].type);
		}

		TEST_METHOD(DoubleoveStoresRightValueWhenMovingValue)
		{
			VM vm;
			const int destRegister = 5;
			const double value = 359.254;

			Operand<double> op1;
			op1.SetValue(value);

			Move<double> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual(value, vm.m_registers[destRegister].values.double_value, 0.01);
		}

		TEST_METHOD(DoubleMoveStoresRightTypeWhenMovingRegister)
		{
			VM vm;
			const int destRegister = 5;
			const int srcRegister = 2;
			const double value = 35;

			vm.m_registers[srcRegister].values.double_value = value;

			Operand<double> op1;
			op1.SetRegister(srcRegister);

			Move<double> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual((int)ObjectType::DOUBLE, (int)vm.m_registers[destRegister].type);
		}

		TEST_METHOD(DoubleMoveStoresRightValueWhenMovingRegister)
		{
			VM vm;
			const int destRegister = 5;
			const int srcRegister = 2;
			const double value = 351.23;

			vm.m_registers[srcRegister].values.double_value = value;

			Operand<double> op1;
			op1.SetRegister(srcRegister);

			Move<double> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual(value, vm.m_registers[destRegister].values.double_value, 0.01);
		}

		TEST_METHOD(CharMoveStoresRightTypeWhenMovingValue)
		{
			VM vm;
			const int destRegister = 5;
			const char value = 'b';

			Operand<char> op1;
			op1.SetValue(value);

			Move<char> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual((int)ObjectType::CHAR, (int)vm.m_registers[destRegister].type);
		}

		TEST_METHOD(CharMoveStoresRightValueWhenMovingValue)
		{
			VM vm;
			const int destRegister = 5;
			const char value = 'a';

			Operand<char> op1;
			op1.SetValue(value);

			Move<char> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual(value, vm.m_registers[destRegister].values.char_value);
		}

		TEST_METHOD(CharMoveStoresRightTypeWhenMovingRegister)
		{
			VM vm;
			const int destRegister = 5;
			const int srcRegister = 2;
			const char value = 'v';

			vm.m_registers[srcRegister].values.char_value = value;

			Operand<char> op1;
			op1.SetRegister(srcRegister);

			Move<char> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual((int)ObjectType::CHAR, (int)vm.m_registers[destRegister].type);
		}

		TEST_METHOD(CharMoveStoresRightValueWhenMovingRegister)
		{
			VM vm;
			const int destRegister = 5;
			const int srcRegister = 2;
			const char value = 'y';

			vm.m_registers[srcRegister].values.char_value = value;

			Operand<char> op1;
			op1.SetRegister(srcRegister);

			Move<char> move(op1, destRegister);
			move.Execute(&vm);

			Assert::AreEqual(value, vm.m_registers[destRegister].values.char_value);
		}

	};
}