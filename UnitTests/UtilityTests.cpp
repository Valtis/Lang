#include "stdafx.h"
#include "CppUnitTest.h"
#include "VM.h"
#include "Instructions/UtilityInstructions.h"

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

	};
}