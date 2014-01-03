#include "stdafx.h"
#include "CppUnitTest.h"
#include "Instructions/Operand.h"
#include "VM.h"
#include "VMObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(OperandTest)
	{
	public:

		TEST_METHOD(OperandReturnsCorrectIntValue)
		{
			const int value = 25;
			Operand<int> operand;
			operand.SetValue(value);
			Assert::AreEqual(value, operand.GetValue(nullptr));
		}

		TEST_METHOD(OperandReturnsCorrectNegativeIntValue)
		{
			const int value = -25;
			Operand<int> operand;
			operand.SetValue(value);
			Assert::AreEqual(value, operand.GetValue(nullptr));
		}

		TEST_METHOD(OperandReturnsCorrectIntValueFromRegister)
		{
			const int reg = 4;
			const int value = 12345;
			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value;
			vm.m_registers[reg] = o;
						
			Operand<int> operand;
			operand.SetRegister(reg);
			Assert::AreEqual(value, operand.GetValue(&vm));
		}

		TEST_METHOD(OperandReturnsCorrectDoubleValue)
		{
			const double value = 123.45;
			Operand<double> operand;
			operand.SetValue(value);
			Assert::AreEqual(value, operand.GetValue(nullptr), 0.01);
		}

		TEST_METHOD(OperandReturnsCorrectDoubleValueFromRegister)
		{
			const int reg = 13;
			const double value = 12345.123;
			VM vm;
			VMObject o;
			o.type = ObjectType::DOUBLE;
			o.values.double_value = value;
			vm.m_registers[reg] = o;

			Operand<double> operand;
			operand.SetRegister(reg);
			Assert::AreEqual(value, operand.GetValue(&vm), 0.01);
		}

		TEST_METHOD(OperandReturnsCorrectCharValue)
		{
			const char value = 'a';
			Operand<char> operand;
			operand.SetValue(value);
			Assert::AreEqual(value, operand.GetValue(nullptr));
		}

		TEST_METHOD(OperandReturnsCorrectCharValueFromRegister)
		{
			const int reg = 0;
			const char value = 'y';
			VM vm;
			VMObject o;
			o.type = ObjectType::CHAR;
			o.values.char_value = value;
			vm.m_registers[reg] = o;

			Operand<char> operand;
			operand.SetRegister(reg);
			Assert::AreEqual(value, operand.GetValue(&vm));
		}

		TEST_METHOD(OperandThrowsIfRegisterIsNegative)
		{
			const int reg = -1;
		
			Operand<char> operand;
			Assert::ExpectException<runtime_error>([&]() { operand.SetRegister(reg); });
		}

		TEST_METHOD(OperandThrowsIfRegisterIsTooLarge)
		{
			const int reg = REGISTER_CNT;

			Operand<char> operand;
			Assert::ExpectException<runtime_error>([&]() { operand.SetRegister(reg); });
		}

	};
}