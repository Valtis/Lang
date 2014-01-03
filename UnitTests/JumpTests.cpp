#include "stdafx.h"
#include "CppUnitTest.h"
#include "Instructions/JumpCommands.h"
#include "VM.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(JumpTest)
	{
	public:

		TEST_METHOD(JumpThrowsIfLabelIsWrong)
		{
			VM vm;

			Jump jump("foo");
			Assert::ExpectException<runtime_error>([&]() { jump.Execute(&vm); });
		}

		TEST_METHOD(JumpMovesInstructionPointerToCorrectPosition)
		{
			VM vm;
			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;

			Jump jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpNotEqualThrowsIfLabelIsWrong)
		{
			VM vm;
			JumpNotEqual jump("foo");
			Assert::ExpectException<runtime_error>([&]() { jump.Execute(&vm); });
		}

		TEST_METHOD(JumpNotEqualMovesInstructionPointerToCorrectPositionWhenComparisonIsGreater)
		{
			VM vm;
			
			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpNotEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpNotEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpNotEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpNotEqualMovesInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpNotEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpNotEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpNotEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfEqualThrowsIfLabelIsWrong)
		{
			VM vm;
			JumpIfEqual jump("foo");
			Assert::ExpectException<runtime_error>([&]() { jump.Execute(&vm); });
		}

		TEST_METHOD(JumpIfEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsGreater)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfEqualMovesInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfLessThrowsIfLabelIsWrong)
		{
			VM vm;
			JumpIfLess jump("foo");
			Assert::ExpectException<runtime_error>([&]() { jump.Execute(&vm); });
		}

		TEST_METHOD(JumpIfLessDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsGreater)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfLess jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfLessDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfLess jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfLessMovesInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfLess jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfLessDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfLess jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfGreaterThrowsIfLabelIsWrong)
		{
			VM vm;
			JumpIfGreater jump("foo");
			Assert::ExpectException<runtime_error>([&]() { jump.Execute(&vm); });
		}

		TEST_METHOD(JumpIfGreaterMovesInstructionPointerToCorrectPositionWhenComparisonIsGreater)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfGreater jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfGreater jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfGreater jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = 25;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfGreater jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instructionPointer);
		}
	};
}