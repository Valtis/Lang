#include "stdafx.h"
#include "CppUnitTest.h"
#include "Instructions/StackOperations.h"
#include "VM.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(StackOperationsTest)
	{
	public:

		TEST_METHOD(PushModifiesStackPointer)
		{
			VM vm;
			const int reg = 4;
			vm.m_registers[reg].type = ObjectType::INTEGER;
			vm.m_registers[reg].values.integer_value = 45;

			Push push(reg);
			push.Execute(&vm);

			Assert::AreEqual(1, vm.m_stack_ptr);

		}

		TEST_METHOD(PushPushesCorrectRegisterIntoStack)
		{
			VM vm;
			const int reg = 4;
			const int value = 232;
			vm.m_registers[reg].type = ObjectType::INTEGER;
			vm.m_registers[reg].values.integer_value = value;
			
			Push push(reg);
			push.Execute(&vm);

			Assert::AreEqual(value, vm.m_stack[0].values.integer_value);
		}

		TEST_METHOD(PushModifiesStackPointerWhenPushingEmptyValue)
		{
			VM vm;
			const int reg = -1;
			Push push(reg);
			push.Execute(&vm);

			Assert::AreEqual(1, vm.m_stack_ptr);

		}

		TEST_METHOD(PushPushesCorrectEmptyValueIntoStack)
		{
			VM vm;
			const int reg = -1;
			
			Push push(reg);
			push.Execute(&vm);

			Assert::AreEqual((int)ObjectType::UNINITIALIZED, (int)vm.m_stack[0].type);
		}


		TEST_METHOD(PopModifiesStackCorrectly)
		{
			VM vm;
			VMObject o;
			vm.Push(o);
			Pop pop(2);
			pop.Execute(&vm);
			Assert::AreEqual(0, vm.m_stack_ptr);
		}

		TEST_METHOD(PopModifiesCorrectRegister)
		{
			VM vm;
			const int reg = 4;
			const int value = 2345;
			VMObject o;
			o.type = ObjectType::INTEGER;
			o.values.integer_value = value;
			vm.Push(o);
			
			Pop pop(reg);
			pop.Execute(&vm);

			Assert::AreEqual(value, vm.m_registers[reg].values.integer_value);
		}


	};
}