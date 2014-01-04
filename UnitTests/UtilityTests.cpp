#include "stdafx.h"
#include "CppUnitTest.h"
#include "VM.h"
#include "Instructions/UtilityInstructions.h"
#include "InstructionFormer.h"
#include "Tokens.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(UtilityTest)
	{
	public:

		TEST_METHOD(EndInstructionSetsEndFlag)
		{
			VM vm;

			End end;
			end.Execute(&vm);

			Assert::IsTrue(vm.m_endExecution);
		}


			
		TEST_METHOD(FunctionCallWorksCorrectly)
		{
			VM vm;
			std::vector<std::vector<std::string>> instructions = {
				{ INTEGER_MOVE, "20", "r0" },
				{ ALLOCATE_INTEGER_POINTER, "r0", "r1" },
				{ PUSH, "r1" },
				{ PUSH, "r0" },
				{ CALLSUB, "foo" },
				{ "foo:" },
				{ PUSH, "r0" },
				{ PUSH, "r1" },
				{ STACK_READ, "-2", "r1" },
				{ STACK_READ, "-1", "r0" }
			};

			auto instr = InstructionFormer::FormInstructions(instructions);

			for (auto &i : instr)
			{
				i->Execute(&vm);
			}


			Assert::AreEqual(2, vm.m_frame_ptr);
			Assert::AreEqual((int)ObjectType::INTEGER, (int)vm.m_registers[0].type);
			Assert::AreEqual(20, vm.m_registers[0].values.integer_value);
			
			Assert::AreEqual((int)ObjectType::INTEGER_PTR, (int)vm.m_registers[1].type);

		}

	};
}