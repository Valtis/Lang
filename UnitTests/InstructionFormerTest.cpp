#include "stdafx.h"
#include "CppUnitTest.h"
#include "InstructionFormer.h"
#include "Instructions/ArithmeticOperations.h"
#include "Instructions/JumpCommands.h"
#include "Tokens.h"
#include <vector>
#include <string>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(InstructionFormerTest)
	{
	public:
		TEST_METHOD(InstructionFormerFormsMultipleInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { INTEGER_ADDITION, "r0", "5", "r3" }, { INTEGER_MULTIPLICATION, "r2", "r5", "r3" }, { JUMP, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			Assert::IsNotNull(dynamic_cast <Addition<int> *>(instructions[0].get()));
			Assert::IsNotNull(dynamic_cast <Multiplication<int> *>(instructions[1].get()));
			Assert::IsNotNull(dynamic_cast <Jump *>(instructions[2].get()));

		}

		TEST_METHOD(InstructionFormerFormsAdditionInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { INTEGER_ADDITION, "r0", "5", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast < Addition<int> *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerAdditionInstructionWorksCorrectlyWhenBothOperandsAreValues)
		{
			VM vm;
			vector<vector<string>> fileTokens = { { INTEGER_ADDITION, "6", "5", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			
			instructions[0]->Execute(&vm);

			Assert::AreEqual(11, vm.m_registers[3].values.integer_value);
		}

		TEST_METHOD(InstructionFormerAdditionInstructionWorksCorrectlyWhenOperandsAreMixed)
		{
			VM vm;
			vm.m_registers[6].type = ObjectType::INTEGER;
			vm.m_registers[6].values.integer_value = 6;

			vector<vector<string>> fileTokens = { { INTEGER_ADDITION, "r6", "5", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			instructions[0]->Execute(&vm);

			Assert::AreEqual(11, vm.m_registers[3].values.integer_value);
		}

		TEST_METHOD(InstructionFormerFormsSubstractionInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { INTEGER_SUBSTRACTION, "r0", "5", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <Substraction<int> *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerSubstractionInstructionWorksCorrectlyWhenBothOperandsAreValues)
		{
			VM vm;
			vector<vector<string>> fileTokens = { { INTEGER_SUBSTRACTION, "6", "5", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			instructions[0]->Execute(&vm);

			Assert::AreEqual(1, vm.m_registers[3].values.integer_value);
		}

		TEST_METHOD(InstructionFormerSubstractionInstructionWorksCorrectlyWhenOperandsAreMixed)
		{
			VM vm;
			vm.m_registers[6].type = ObjectType::INTEGER;
			vm.m_registers[6].values.integer_value = 6;

			vector<vector<string>> fileTokens = { { INTEGER_SUBSTRACTION, "7", "r6", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			instructions[0]->Execute(&vm);

			Assert::AreEqual(1, vm.m_registers[3].values.integer_value);
		}

		TEST_METHOD(InstructionFormerFormsMultiplicationInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { INTEGER_MULTIPLICATION, "r0", "5", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <Multiplication<int> *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerMultiplicationInstructionWorksCorrectlyWhenBothOperandsAreValues)
		{
			VM vm;
			vector<vector<string>> fileTokens = { { INTEGER_MULTIPLICATION, "6", "5", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			instructions[0]->Execute(&vm);

			Assert::AreEqual(30, vm.m_registers[3].values.integer_value);
		}

		TEST_METHOD(InstructionFormerMultiplicationInstructionWorksCorrectlyWhenOperandsAreBothRegisters)
		{
			VM vm;
			vm.m_registers[6].type = ObjectType::INTEGER;
			vm.m_registers[6].values.integer_value = 6;
			vm.m_registers[0].type = ObjectType::INTEGER;
			vm.m_registers[0].values.integer_value = 10;

			vector<vector<string>> fileTokens = { { INTEGER_MULTIPLICATION, "r0", "r6", "r7" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			instructions[0]->Execute(&vm);

			Assert::AreEqual(60, vm.m_registers[7].values.integer_value);
		}

		TEST_METHOD(InstructionFormerFormsDivisionInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { INTEGER_DIVISION, "r0", "5", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <Division<int> *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerDivisionInstructionWorksCorrectlyWhenBothOperandsAreValues)
		{
			VM vm;
			vector<vector<string>> fileTokens = { { INTEGER_DIVISION, "6", "3", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			instructions[0]->Execute(&vm);

			Assert::AreEqual(2, vm.m_registers[3].values.integer_value);
		}

		TEST_METHOD(InstructionFormerDivisionInstructionWorksCorrectlyWhenOperandsAreBothRegisters)
		{
			VM vm;
			vm.m_registers[6].type = ObjectType::INTEGER;
			vm.m_registers[6].values.integer_value = 30;
			vm.m_registers[0].type = ObjectType::INTEGER;
			vm.m_registers[0].values.integer_value = 7;

			vector<vector<string>> fileTokens = { { INTEGER_DIVISION, "r6", "r0", "r7" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			instructions[0]->Execute(&vm);

			Assert::AreEqual(4, vm.m_registers[7].values.integer_value);
		}

		TEST_METHOD(InstructionFormerFormsJumpInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { JUMP, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <Jump *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerJumpHasCorrectLabel)
		{
			vector<vector<string>> fileTokens = { { JUMP, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);

			Assert::AreEqual(std::string("foo"), dynamic_cast<Jump *>(instructions[0].get())->GetLabel());
		}

		TEST_METHOD(InstructionFormerFormsJumpNotEqualInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { JUMP_NOT_EQUAL, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <Jump *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerJumpNotEqualHasCorrectLabel)
		{
			vector<vector<string>> fileTokens = { { JUMP_NOT_EQUAL, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::AreEqual(std::string("foo"), dynamic_cast<Jump *>(instructions[0].get())->GetLabel());
		}

		TEST_METHOD(InstructionFormerFormsJumpIfEqualInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { JUMP_IF_EQUAL, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <Jump *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerJumpIfEqualHasCorrectLabel)
		{
			vector<vector<string>> fileTokens = { { JUMP_IF_EQUAL, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::AreEqual(std::string("foo"), dynamic_cast<Jump *>(instructions[0].get())->GetLabel());
		}

		TEST_METHOD(InstructionFormerFormsJumpIfLesserInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { JUMP_IF_LESSER, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <Jump *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerJumpIfLesserHasCorrectLabel)
		{
			vector<vector<string>> fileTokens = { { JUMP_IF_LESSER, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::AreEqual(std::string("foo"), dynamic_cast<Jump *>(instructions[0].get())->GetLabel());
		}

		TEST_METHOD(InstructionFormerFormsJumpIfGreaterInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { JUMP_IF_GREATER, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <Jump *>(instructions[0].get()));
		}

		TEST_METHOD(InstructionFormerJumpIfGreaterHasCorrectLabel)
		{
			vector<vector<string>> fileTokens = { { JUMP_IF_GREATER, "foo" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::AreEqual(std::string("foo"), dynamic_cast<Jump *>(instructions[0].get())->GetLabel());
		}

		TEST_METHOD(InstructionFormerFormsIntegerRandomizationInstructionCorrectly)
		{
			vector<vector<string>> fileTokens = { { INTEGER_RANDOMIZE, "r1", "r2", "r3" } };
			vector<std::unique_ptr<Instruction>> instructions = InstructionFormer::FormInstructions(fileTokens);
			Assert::IsNotNull(dynamic_cast <RandomizeInteger *>(instructions[0].get()));
		}

	};
}