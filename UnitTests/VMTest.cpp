#include "stdafx.h"
#include "CppUnitTest.h"
#include "VM.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(VMTest)
	{
	public:

		TEST_METHOD(VMThrowsOnStackOverflow)
		{
			VM vm;
			vm.m_stack_ptr = STACK_SIZE;
			VMObject o;
			Assert::ExpectException<runtime_error>([&]() { vm.Push(o); });
		}

		TEST_METHOD(VMStackPointsToCorrectLocationAfterPush)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			Assert::AreEqual(1, vm.m_stack_ptr);
		}


		TEST_METHOD(VMStackPointsToCorrectLocationAfterMultiplePushes)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.Push(o);
			Assert::AreEqual(3, vm.m_stack_ptr);
		}


		TEST_METHOD(VMThrowsOnStackUnderflow)
		{
			VM vm;
			Assert::ExpectException<runtime_error>([&]() { vm.Pop(); });
		}

		TEST_METHOD(VMStackPointsToCorrectLocationAfterPushAndPop)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Pop();
			Assert::AreEqual(0, vm.m_stack_ptr);
		}

		TEST_METHOD(VMStackPointsToCorrectLocationAfterMultiplePushesAndPops)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			vm.Push(o);
			vm.Push(o);
			vm.Pop();
			vm.Pop();
			vm.Pop();
			Assert::AreEqual(0, vm.m_stack_ptr);
		}

		TEST_METHOD(VMPopReturnsCorrectValue)
		{
			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;
			
			o.values.integer_value = 12345;
			vm.Push(o);
			VMObject newObject = vm.Pop();
			Assert::AreEqual(12345, newObject.values.integer_value);
		}


		TEST_METHOD(VMPopReturnsCorrectValueAfterMultiplePushesAndPops)
		{

			VM vm;
			VMObject o;
			o.type = ObjectType::INTEGER;

			o.values.integer_value = 1;
			vm.Push(o);
			o.values.integer_value = 2;
			vm.Push(o);
			o.values.integer_value = 3;
			vm.Push(o);
			o.values.integer_value = 4;
			vm.Push(o);
			vm.Pop();
			vm.Pop();

			VMObject newObject = vm.Pop();
			Assert::AreEqual(2, newObject.values.integer_value);
		}

	};
}