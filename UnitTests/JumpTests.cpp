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
			vm.m_jumpositions["foo"] = pos;

			Jump jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
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
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpNotEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpNotEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpNotEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpNotEqualMovesInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpNotEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpNotEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpNotEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
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
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfEqualMovesInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfEqual jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
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
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfLess jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfLessDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfLess jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfLessMovesInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfLess jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfLessDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfLess jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
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
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfGreater jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfGreater jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfGreater jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfGreater jump("foo");
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}


		TEST_METHOD(CallSubAddsCorrectNumberOfItemsToStack)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;
			
			CallSub sub("foo");
			sub.Execute(&vm);
			Assert::AreEqual(2, vm.m_stack_ptr);
		}

		TEST_METHOD(CallSubAddsCorrectNumberOfItemsToStackWhenStackAlreadyHasItems)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.Push(o);


			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;

			CallSub sub("foo");
			sub.Execute(&vm);
			Assert::AreEqual(5, vm.m_stack_ptr);
		}

		TEST_METHOD(CallSubAddsCorrectNumberOfItemsToStackAfterSecondCall)
		{
			VM vm;

			const int pos = 25;
			vm.m_jumpositions["foo"] = pos;

			CallSub sub("foo");
			sub.Execute(&vm);
			sub.Execute(&vm);

			Assert::AreEqual(4, vm.m_stack_ptr);
		}

		TEST_METHOD(CallSubMovesInstructionPointerCorrectly)
		{
			VM vm;

			const int pos = 300;
			vm.m_jumpositions["foo"] = pos;

			CallSub sub("foo");
			sub.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}



		TEST_METHOD(CallSubMovesInstructionPointerCorrectlyAfterSecondCall)
		{
			VM vm;

			const int pos = 300;
			const int pos2 = 500;
			vm.m_jumpositions["foo"] = pos;

			vm.m_jumpositions["bar"] = pos2;

			CallSub sub("foo");
			CallSub sub2("bar");
			sub.Execute(&vm);
			sub2.Execute(&vm);
			Assert::AreEqual(pos2, vm.m_instruction_ptr);
		}

		TEST_METHOD(CallSubStoresFramePointerCorrectly)
		{
			VM vm;
			VMObject foo;
			vm.Push(foo);
			vm.Push(foo);
			vm.Push(foo);
			vm.Push(foo);

			const int pos = 300;
			vm.m_jumpositions["foo"] = pos;

			CallSub sub("foo");
			sub.Execute(&vm);
			vm.Pop();
			auto framePtr = vm.Pop();


			Assert::AreEqual(0, framePtr.values.integer_value);
		}

		TEST_METHOD(CallSubStoresFramePointerCorrectlyAfterSecondCall)
		{
			VM vm;
			VMObject foo;
			vm.Push(foo);
			vm.Push(foo);
			vm.Push(foo);
			vm.Push(foo);

			const int pos = 300;
			vm.m_jumpositions["foo"] = pos;

			CallSub sub("foo");
			sub.Execute(&vm);
			sub.Execute(&vm);
			vm.Pop();
			auto framePtr = vm.Pop();


			Assert::AreEqual(4, framePtr.values.integer_value);
		}

		TEST_METHOD(CallSubStoresInstructionPointerCorrectly)
		{
			VM vm;
			VMObject foo;

			const int pos = 300;
			vm.m_jumpositions["foo"] = pos;

			CallSub sub("foo");
			sub.Execute(&vm);
			auto instructionPtr = vm.Pop();
			

			Assert::AreEqual(0, instructionPtr.values.integer_value);
		}

		TEST_METHOD(CallSubStoresInstructionPointerCorrectlyAfterSecondCall)
		{
			VM vm;
			VMObject foo;

			const int pos = 300;
			const int pos2 = 500;
			
			vm.m_jumpositions["foo"] = pos;
			vm.m_jumpositions["bar"] = pos2;


			CallSub sub("foo");
			CallSub sub2("bar");
			sub.Execute(&vm);
			sub2.Execute(&vm);
			auto instructionPtr = vm.Pop();


			Assert::AreEqual(pos, instructionPtr.values.integer_value);
		}

		TEST_METHOD(RetThrowsOnNegativePopCount)
		{
			Assert::ExpectException<runtime_error>([]() { Ret a(-1);  });
		}


		TEST_METHOD(StackOnSameStateAfterSubCallAndReturnWithNoParameters)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(0);

			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(2, vm.m_stack_ptr);
		}

		TEST_METHOD(InstructionPointerReturnedToCorrectValueAfterSubCallAndReturnWithNoParameters)
		{
			VM vm;
			vm.m_instruction_ptr = 15;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(0);

			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(15, vm.m_instruction_ptr);
		}

		TEST_METHOD(FramePointerReturnedToCorrectValueAfterSubCallAndReturnWithNoParameters)
		{
			VM vm;
			vm.m_frame_ptr = 15;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(0);

			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(15, vm.m_frame_ptr);
		}

		TEST_METHOD(StackOnSameStateAfterSubCallAndReturnWithParameters)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(2);

			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(0, vm.m_stack_ptr);
		}

		TEST_METHOD(InstructionPointerReturnedToCorrectValueAfterSubCallAndReturnWithParameters)
		{
			VM vm;
			vm.m_instruction_ptr = 15;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(2);

			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(15, vm.m_instruction_ptr);
		}

		TEST_METHOD(FramePointerReturnedToCorrectValueAfterSubCallAndReturnWithParameters)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(2);

			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(0, vm.m_frame_ptr);
		}


		TEST_METHOD(StackOnSameStateAfterSubCallAndReturnWithNoParametersAndMultipleCalls)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(0);

			sub.Execute(&vm);
			sub.Execute(&vm);
			ret.Execute(&vm);
			
			Assert::AreEqual(4, vm.m_stack_ptr);
		}

		TEST_METHOD(InstructionPointerReturnedToCorrectValueAfterSubCallAndReturnWithNoParametersAndMultipleCalls)
		{
			VM vm;
			vm.m_instruction_ptr = 15;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;
			vm.m_jumpositions["bar"] = 23;

			CallSub sub("foo");
			CallSub sub2("bar");
			Ret ret(0);

			sub.Execute(&vm);
			sub2.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(423, vm.m_instruction_ptr);
		}

		TEST_METHOD(FramePointerReturnedToCorrectValueAfterSubCallAndReturnWithNoParametersAndMultipleCalls)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(0);

			sub.Execute(&vm);
			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(2, vm.m_frame_ptr);
		}

		TEST_METHOD(StackOnSameStateAfterSubCallAndReturnWithParametersAndMultipleCalls)
		{
			VM vm;
			VMObject o;
			
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(2);

			vm.Push(o);
			vm.Push(o);
			sub.Execute(&vm);
			vm.Push(o);
			vm.Push(o);
			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(4, vm.m_stack_ptr);
		}

		TEST_METHOD(StackOnSameStateAfterSubCallAndReturnWithParametersAndMultipleCallsAndReturns)
		{
			VM vm;
			VMObject o;

			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(2);

			vm.Push(o);
			vm.Push(o);
			sub.Execute(&vm);
			vm.Push(o);
			vm.Push(o);
			sub.Execute(&vm);
			ret.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(0, vm.m_stack_ptr);
		}

		TEST_METHOD(InstructionPointerReturnedToCorrectValueAfterSubCallAndReturnWithParametersAndMultipleCalls)
		{
			VM vm;
			vm.m_instruction_ptr = 15;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;
			vm.m_jumpositions["bar"] = 23;

			CallSub sub("foo");
			CallSub sub2("bar");
			Ret ret(2);



			sub.Execute(&vm);
			vm.Push(o);
			vm.Push(o);
			sub2.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(423, vm.m_instruction_ptr);
		}

		TEST_METHOD(FramePointerReturnedToCorrectValueAfterSubCallAndReturnWithParametersAndMultipleCalls)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.m_jumpositions["foo"] = 423;

			CallSub sub("foo");
			Ret ret(2);

			sub.Execute(&vm);

			vm.Push(o);
			vm.Push(o);
			sub.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(2, vm.m_frame_ptr);
		}

	};
}