#include "stdafx.h"
#include "CppUnitTest.h"
#include "Instructions/Operand.h"
#include "Instructions/Instruction.h"
#include "Instructions/ArithmeticOperations.h"
#include "VM.h"
#include "VMObject.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(ArithmeticInstructionTest)
	{
	public:

		TEST_METHOD(IntegerAdditionResultRegisterHasCorrectTypeWhenOperandsAreValues)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int result = value1 + value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetValue(value2);

			VM vm;
			Addition<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerAdditionResultRegisterHasCorrectValueWhenOperandsAreValues)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int result = value1 + value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetValue(value2);

			VM vm;
			Addition<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerAdditionResultRegisterHasCorrectTypeWhenOperandsAreMixed1)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int readRegister = 4;
			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value2;
			vm.m_registers[readRegister] = o;


			const int result = value1 + value2;
			const int storeRegister = 9;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetRegister(readRegister);

			
			Addition<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerAdditionResultRegisterHasCorrectValueWhenOperandsAreMixed1)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int readRegister = 4;
			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value2;
			vm.m_registers[readRegister] = o;


			const int result = value1 + value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetRegister(readRegister);


			Addition<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerAdditionResultRegisterHasCorrectTypeWhenOperandsAreMixed2)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int readRegister = 1;
			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;


			const int result = value1 + value2;
			const int storeRegister = 9;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetValue(value2);


			Addition<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerAdditionResultRegisterHasCorrectValueWhenOperandsAreMixed2)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int readRegister = 1;
			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;


			const int result = value1 + value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetValue(value2);


			Addition<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}


		TEST_METHOD(IntegerAdditionResultRegisterHasCorrectTypeWhenOperandsAreRegisters)
		{
			const int value1 = 3223;
			const int value2 = 34324;
			const int readRegister = 1;
			const int readRegister2 = 0;
			const int storeRegister = 9;
			const int result = value1 + value2;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;
			
			o.values.integer_value = value2;
			vm.m_registers[readRegister2] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetRegister(readRegister2);


			Addition<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerAdditionResultRegisterHasCorrectValueWhenOperandsAreRegisters)
		{
			const int value1 = 2;
			const int value2 = 3432412;
			const int readRegister = 1;
			const int readRegister2 = 3;
			const int storeRegister = 9;
			const int result = value1 + value2;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			o.values.integer_value = value2;
			vm.m_registers[readRegister2] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetRegister(readRegister2);


			Addition<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}


		TEST_METHOD(IntegerSubstractionResultRegisterHasCorrectTypeWhenOperandsAreValues)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int result = value1 - value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetValue(value2);

			VM vm;
			Substraction<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerSubstractionResultRegisterHasCorrectValueWhenOperandsAreValues)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int result = value1 - value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetValue(value2);

			VM vm;
			Substraction<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerSubstractionResultRegisterHasCorrectTypeWhenOperandsAreMixed1)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int readRegister = 4;
			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value2;
			vm.m_registers[readRegister] = o;


			const int result = value1 - value2;
			const int storeRegister = 9;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetRegister(readRegister);


			Substraction<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerSubstractionResultRegisterHasCorrectValueWhenOperandsAreMixed1)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int readRegister = 4;
			const int result = value1 - value2;
			const int storeRegister = REGISTER_CNT - 1;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value2;
			vm.m_registers[readRegister] = o;


			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetRegister(readRegister);


			Substraction<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerSubstractionResultRegisterHasCorrectTypeWhenOperandsAreMixed2)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int readRegister = 1;
			const int result = value1 - value2;
			const int storeRegister = 9;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetValue(value2);


			Substraction<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerSubstractionResultRegisterHasCorrectValueWhenOperandsAreMixed2)
		{
			const int value1 = 3223;
			const int value2 = 23432;
			const int readRegister = 1; 
			
			const int result = value1 - value2;
			const int storeRegister = REGISTER_CNT - 1;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			Operand<int> op1;
			Operand<int> op2;
			
			op1.SetRegister(readRegister);
			op2.SetValue(value2);
			
			Substraction<int> instruction(op1, op2, storeRegister);
			
			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}


		TEST_METHOD(IntegerSubstractionResultRegisterHasCorrectTypeWhenOperandsAreRegisters)
		{
			const int value1 = 3223;
			const int value2 = 12;
			const int readRegister = 1;
			const int readRegister2 = 0;
			const int storeRegister = 9;
			const int result = value1 - value2;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			o.values.integer_value = value2;
			vm.m_registers[readRegister2] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetRegister(readRegister2);


			Substraction<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerSubstractionResultRegisterHasCorrectValueWhenOperandsAreRegisters)
		{
			const int value1 = 2;
			const int value2 = 121;
			const int readRegister = 1;
			const int readRegister2 = 3;
			const int storeRegister = 9;
			const int result = value1 - value2;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			o.values.integer_value = value2;
			vm.m_registers[readRegister2] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetRegister(readRegister2);


			Substraction<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerMultiplicationResultRegisterHasCorrectTypeWhenOperandsAreValues)
		{
			const int value1 = 1231;
			const int value2 = 12;
			const int result = value1 * value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetValue(value2);

			VM vm;
			Multiplication<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerMultiplicationResultRegisterHasCorrectValueWhenOperandsAreValues)
		{
			const int value1 = 23123;
			const int value2 = 123;
			const int result = value1 * value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetValue(value2);

			VM vm;
			Multiplication<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerMultiplicationResultRegisterHasCorrectTypeWhenOperandsAreMixed1)
		{
			const int value1 = 2311;
			const int value2 = 8;
			const int readRegister = 4;
			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value2;
			vm.m_registers[readRegister] = o;


			const int result = value1 * value2;
			const int storeRegister = 9;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetRegister(readRegister);


			Multiplication<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerMultiplicationResultRegisterHasCorrectValueWhenOperandsAreMixed1)
		{
			const int value1 = 3223;
			const int value2 = 9;
			const int readRegister = 4;
			const int result = value1 * value2;
			const int storeRegister = REGISTER_CNT - 1;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value2;
			vm.m_registers[readRegister] = o;


			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetRegister(readRegister);


			Multiplication<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerMultiplicationResultRegisterHasCorrectTypeWhenOperandsAreMixed2)
		{
			const int value1 = 3223;
			const int value2 = 8;
			const int readRegister = 1;
			const int result = value1 * value2;
			const int storeRegister = 9;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetValue(value2);


			Multiplication<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerMultiplicationResultRegisterHasCorrectValueWhenOperandsAreMixed2)
		{
			const int value1 = 3223;
			const int value2 = 2;
			const int readRegister = 1;

			const int result = value1 * value2;
			const int storeRegister = REGISTER_CNT - 1;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			Operand<int> op1;
			Operand<int> op2;

			op1.SetRegister(readRegister);
			op2.SetValue(value2);

			Multiplication<int> instruction(op1, op2, storeRegister);

			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}


		TEST_METHOD(IntegerMultiplicationResultRegisterHasCorrectTypeWhenOperandsAreRegisters)
		{
			const int value1 = 3223;
			const int value2 = 12;
			const int readRegister = 1;
			const int readRegister2 = 0;
			const int storeRegister = 9;
			const int result = value1 * value2;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			o.values.integer_value = value2;
			vm.m_registers[readRegister2] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetRegister(readRegister2);


			Multiplication<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerMultiplicationResultRegisterHasCorrectValueWhenOperandsAreRegisters)
		{
			const int value1 = 1222;
			const int value2 = 121;
			const int readRegister = 1;
			const int readRegister2 = 3;
			const int storeRegister = 9;
			const int result = value1 * value2;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			o.values.integer_value = value2;
			vm.m_registers[readRegister2] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetRegister(readRegister2);


			Multiplication<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerDivisionResultRegisterHasCorrectTypeWhenOperandsAreValues)
		{
			const int value1 = 1231;
			const int value2 = 12;
			const int result = value1 / value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetValue(value2);

			VM vm;
			Division<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerDivisionResultRegisterHasCorrectValueWhenOperandsAreValues)
		{
			const int value1 = 23123;
			const int value2 = 123;
			const int result = value1 / value2;
			const int storeRegister = REGISTER_CNT - 1;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetValue(value2);

			VM vm;
			Division<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerDivisionResultRegisterHasCorrectTypeWhenOperandsAreMixed1)
		{
			const int value1 = 2311;
			const int value2 = 8;
			const int readRegister = 4;
			const int result = value1 / value2;
			const int storeRegister = 9;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value2;
			vm.m_registers[readRegister] = o;


			

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetRegister(readRegister);


			Division<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerDivisionResultRegisterHasCorrectValueWhenOperandsAreMixed1)
		{
			const int value1 = 3223;
			const int value2 = 9;
			const int readRegister = 4;
			const int result = value1 / value2;
			const int storeRegister = REGISTER_CNT - 1;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value2;
			vm.m_registers[readRegister] = o;


			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(value1);
			op2.SetRegister(readRegister);


			Division<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerDivisionResultRegisterHasCorrectTypeWhenOperandsAreMixed2)
		{
			const int value1 = 3223;
			const int value2 = 8;
			const int readRegister = 1;
			const int result = value1 / value2;
			const int storeRegister = 9;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetValue(value2);


			Division<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerDivisionResultRegisterHasCorrectValueWhenOperandsAreMixed2)
		{
			const int value1 = 3223;
			const int value2 = 2;
			const int readRegister = 1;

			const int result = value1 / value2;
			const int storeRegister = REGISTER_CNT - 1;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			Operand<int> op1;
			Operand<int> op2;

			op1.SetRegister(readRegister);
			op2.SetValue(value2);

			Division<int> instruction(op1, op2, storeRegister);

			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}


		TEST_METHOD(IntegerDivisionResultRegisterHasCorrectTypeWhenOperandsAreRegisters)
		{
			const int value1 = 3223;
			const int value2 = 12;
			const int readRegister = 1;
			const int readRegister2 = 0;
			const int storeRegister = 9;
			const int result = value1 / value2;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			o.values.integer_value = value2;
			vm.m_registers[readRegister2] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetRegister(readRegister2);


			Division<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(static_cast<int>(ObjectType::INTEGER), static_cast<int>(vm.m_registers[storeRegister].type));
		}

		TEST_METHOD(IntegerDivisionResultRegisterHasCorrectValueWhenOperandsAreRegisters)
		{
			const int value1 = 1222;
			const int value2 = 121;
			const int readRegister = 1;
			const int readRegister2 = 3;
			const int storeRegister = 9;
			const int result = value1 / value2;

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value1;
			vm.m_registers[readRegister] = o;

			o.values.integer_value = value2;
			vm.m_registers[readRegister2] = o;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetRegister(readRegister);
			op2.SetRegister(readRegister2);


			Division<int> instruction(op1, op2, storeRegister);


			instruction.Execute(&vm);
			Assert::AreEqual(result, vm.m_registers[storeRegister].values.integer_value);
		}

		TEST_METHOD(IntegerDivisionThrowsIfDivisorIsValueAndZero)
		{

			VM vm;

			Operand<int> op1;
			Operand<int> op2;


			op1.SetValue(25);
			op2.SetValue(0);


			Division<int> instruction(op1, op2, 3);
			
			Assert::ExpectException<runtime_error>([&]() { instruction.Execute(&vm); });
		}

		TEST_METHOD(IntegerDivisionThrowsIfDivisorIsRegisterAndZero)
		{
			VM vm;

			Operand<int> op1;
			Operand<int> op2;

			vm.m_registers[10].values.integer_value = 0;

			op1.SetValue(25);
			op2.SetRegister(10);


			Division<int> instruction(op1, op2, 3);

			Assert::ExpectException<runtime_error>([&]() { instruction.Execute(&vm); });
		}

		TEST_METHOD(IntegerRandomizeWorks)
		{
			VM vm;

			Operand<int> op1;
			Operand<int> op2;
						
			op1.SetValue(0);
			op2.SetValue(10);


			RandomizeInteger instruction(op1, op2, 3);
			instruction.Execute(&vm);
			Assert::IsTrue(vm.m_registers[3].values.integer_value >= 0 && vm.m_registers[3].values.integer_value <= 10);
		}

		TEST_METHOD(FloatingRandomizeWorks)
		{
			VM vm;

			Operand<double> op1;
			Operand<double> op2;

			op1.SetValue(0.0);
			op2.SetValue(10.0);


			RandomizeDouble instruction(op1, op2, 3);
			instruction.Execute(&vm);
			Assert::IsTrue(vm.m_registers[3].values.double_value >= 0.0 && vm.m_registers[3].values.double_value <= 10.0);
		}

	};
}