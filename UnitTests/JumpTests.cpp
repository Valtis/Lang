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
				
		TEST_METHOD(JumpMovesInstructionPointerToCorrectPosition)
		{
			VM vm;
			const int pos = 25;
		
			Jump jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}


		TEST_METHOD(JumpNotEqualMovesInstructionPointerToCorrectPositionWhenComparisonIsGreater)
		{
			VM vm;
			
			const int pos = 25;
			
			vm.m_cmpResult = CmpResult::GREATER;
			JumpNotEqual jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpNotEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpNotEqual jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpNotEqualMovesInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpNotEqual jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpNotEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpNotEqual jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsGreater)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfEqual jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfEqualMovesInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfEqual jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfEqual jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfEqualDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfEqual jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfLessDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsGreater)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfLess jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfLessDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfLess jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfLessMovesInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfLess jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfLessDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;
			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfLess jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}


		TEST_METHOD(JumpIfGreaterMovesInstructionPointerToCorrectPositionWhenComparisonIsGreater)
		{
			VM vm;

			const int pos = 25;

			vm.m_cmpResult = CmpResult::GREATER;
			JumpIfGreater jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsEqual)
		{
			VM vm;

			const int pos = 25;

			vm.m_cmpResult = CmpResult::EQUAL;
			JumpIfGreater jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsLesser)
		{
			VM vm;

			const int pos = 25;

			vm.m_cmpResult = CmpResult::LESSER;
			JumpIfGreater jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}

		TEST_METHOD(JumpIfGreaterDoesNotMoveInstructionPointerToCorrectPositionWhenComparisonIsNotPerformed)
		{
			VM vm;

			const int pos = 25;

			vm.m_cmpResult = CmpResult::NO_RESULT;
			JumpIfGreater jump(pos);
			jump.Execute(&vm);
			Assert::AreEqual(0, vm.m_instruction_ptr);
		}


		TEST_METHOD(CallSubAddsCorrectNumberOfItemsToStack)
		{
			VM vm;

			const int pos = 25;
			
			CallSub sub(pos);
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

			CallSub sub(pos);
			sub.Execute(&vm);
			Assert::AreEqual(5, vm.m_stack_ptr);
		}

		TEST_METHOD(CallSubAddsCorrectNumberOfItemsToStackAfterSecondCall)
		{
			VM vm;

			const int pos = 25;

			CallSub sub(pos);
			sub.Execute(&vm);
			sub.Execute(&vm);

			Assert::AreEqual(4, vm.m_stack_ptr);
		}

		TEST_METHOD(CallSubMovesInstructionPointerCorrectly)
		{
			VM vm;

			const int pos = 300;

			CallSub sub(pos);
			sub.Execute(&vm);
			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}



		TEST_METHOD(CallSubMovesInstructionPointerCorrectlyAfterSecondCall)
		{
			VM vm;

			const int pos = 300;
			const int pos2 = 500;

			CallSub sub(pos);
			CallSub sub2(pos2);
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

			CallSub sub(pos);
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

			CallSub sub(pos);
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

			CallSub sub(pos);
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
			
			CallSub sub(pos);
			CallSub sub2(pos2);
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
			const int pos = 423;

			CallSub sub(pos);
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
			const int pos = 423;

			CallSub sub(pos);
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
			const int pos = 423;

			CallSub sub(pos);
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
			const int pos = 423;

			CallSub sub(pos);
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
			const int pos = 423;
			
			CallSub sub(pos);
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
			const int pos = 423;

			CallSub sub(pos);
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
			const int pos = 423;

			CallSub sub(pos);
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
			const int pos = 423;
			const int pos2 = 23;

			CallSub sub(pos);
			CallSub sub2(pos2);
			Ret ret(0);

			sub.Execute(&vm);
			sub2.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(FramePointerReturnedToCorrectValueAfterSubCallAndReturnWithNoParametersAndMultipleCalls)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			const int pos = 423;

			CallSub sub(pos);
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
			
			const int pos = 423;

			CallSub sub(pos);
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

			const int pos = 423;

			CallSub sub(pos);
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

			const int pos = 423;
			const int pos2 = 23;

			CallSub sub(pos);
			CallSub sub2(pos2);
			Ret ret(2);



			sub.Execute(&vm);
			vm.Push(o);
			vm.Push(o);
			sub2.Execute(&vm);
			ret.Execute(&vm);

			Assert::AreEqual(pos, vm.m_instruction_ptr);
		}

		TEST_METHOD(FramePointerReturnedToCorrectValueAfterSubCallAndReturnWithParametersAndMultipleCalls)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			const int pos = 423;

			CallSub sub(pos);
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