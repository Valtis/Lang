#include "stdafx.h"
#include "CppUnitTest.h"
#include "VM.h"
#include "Instructions/IntegerPointerOperations.h"
#include "Instructions/StackOperations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(ToLowerTest)
	{
	public:

		TEST_METHOD(MemoryMangerListsCorrectAllocationCount)
		{
			VM vm;
			const int size = 200;
			const int dest = 5;
			Operand<int> op;

			op.SetValue(size);
			AllocateIntegerPointer allocate(op, dest);
			allocate.Execute(&vm);
			
			Assert::AreEqual((long int)size * 4, vm.m_memoryManager.AllocatedMemory());
		}

		TEST_METHOD(GCDoesNotCollectWhenPointerExists)
		{
			VM vm;
			const int size = 200;
			const int dest = 5;
			Operand<int> op;

			op.SetValue(size);
			AllocateIntegerPointer allocate(op, dest);
			allocate.Execute(&vm);
			vm.m_memoryManager.RunGC(&vm);

			Assert::AreEqual((long int)size * 4, vm.m_memoryManager.AllocatedMemory());
		}

		TEST_METHOD(GCDoesNotCollectWhenPointerIsCopiedAndOriginalErased)
		{
			VM vm;
			const int size = 200;
			const int dest = 5;
			Operand<int> op;

			op.SetValue(size);
			AllocateIntegerPointer allocate(op, dest);
			allocate.Execute(&vm);
			

			vm.m_registers[0] = vm.m_registers[5];
			VMObject o;
			vm.m_registers[5] = o;


			vm.m_memoryManager.RunGC(&vm);
			Assert::AreEqual((long int)size * 4, vm.m_memoryManager.AllocatedMemory());
		}

		TEST_METHOD(GCDoesNotCollectWhenPointerIsStoredInStackAndOriginalErased)
		{
			VM vm;
			const int size = 200;
			const int dest = 5;
			Operand<int> op;

			op.SetValue(size);
			AllocateIntegerPointer allocate(op, dest);
			allocate.Execute(&vm);

			Push push(dest);

			push.Execute(&vm);
			
			VMObject o;
			vm.m_registers[5] = o;


			vm.m_memoryManager.RunGC(&vm);
			Assert::AreEqual((long int)size * 4, vm.m_memoryManager.AllocatedMemory());
		}

		TEST_METHOD(GCCollectsWhenPointerIsLost)
		{
			VM vm;
			const int size = 200;
			const int dest = 5;
			Operand<int> op;

			op.SetValue(size);
			AllocateIntegerPointer allocate(op, dest);
			allocate.Execute(&vm);

			VMObject o;
			vm.m_registers[5] = o;


			vm.m_memoryManager.RunGC(&vm);
			Assert::AreEqual((long int)0, vm.m_memoryManager.AllocatedMemory());
		}

	};
}