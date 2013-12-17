#include "MemoryManager.h"
#include <cstdlib>
#include "VM.h"

#define GC_MIN_THRESHOLD 20
MemoryManager::MemoryManager() : m_gcThreshold(20), m_allocatedMemory(0)
{

}

MemoryManager::~MemoryManager()
{


}


VMObject MemoryManager::Allocate(VM *vm, ObjectType t, int cnt)
{
	VMObject o;
	Ptr *managedPtr = (Ptr *)malloc(sizeof(Ptr));
	if (managedPtr == nullptr)
	{
		RunGC(vm);
		Ptr *managedPtr = (Ptr *)malloc(sizeof(Ptr));
		if (managedPtr == nullptr)
		{
			throw std::runtime_error("Memory allocation failed - out of memory?");
		}
	}
	int size;

	switch (t)
	{
	case ObjectType::INTEGER_PTR:
		size = sizeof(int);
		break;
	case ObjectType::CHAR_PTR:
		size = sizeof(char);
		break;

	case ObjectType::DOUBLE_PTR:
		size = sizeof(double);
		break;


	default:
		throw std::runtime_error("Internal VM error - attempting to allocate non pointer type");
	}

	managedPtr->m_marked = false;
	managedPtr->m_memory_manager_ptr = managedPtr;
	managedPtr->size = cnt*size;
	m_allocatedMemory += managedPtr->size;


	managedPtr->ptr = malloc(managedPtr->size);
	if (managedPtr->ptr == nullptr)
	{
		RunGC(vm);
		managedPtr->ptr = malloc(managedPtr->size);
		if (managedPtr->ptr == nullptr)
		{
			throw std::runtime_error("Memory allocation failed - out of memory?");
		}
	}

	o.type = t;
	o.values.ptr = *managedPtr;
	m_allocatedPointers.push_back(managedPtr);

	return o;
}


void MemoryManager::RunGC(VM *vm)
{
	//printf("Running garbage collector: Memory allocated now: %d bytes\n", m_allocatedMemory);
	int reg = 0;
	for (auto &r : vm->m_registers)
	{

		if (IsPointer(r))
		{
			r.values.ptr.m_memory_manager_ptr->m_marked = true;
		}
		++reg;
	}

	for (int i = 0; i < vm->m_stack_ptr; ++i)
	{
		if (IsPointer(vm->m_stack[i]))
		{
			vm->m_stack[i].values.ptr.m_memory_manager_ptr->m_marked = true;
		}
	}

	auto it = m_allocatedPointers.begin();
	while (it != m_allocatedPointers.end())
	{
		if (!(*it)->m_marked)
		{
			m_allocatedMemory -= (*it)->size;
			free((*it)->ptr);
			free(*it);
			it = m_allocatedPointers.erase(it);
			continue;
		}
		else 
		{
			(*it)->m_marked = false;
		}
		it++;
	}


	//printf("After garbage collection: Memory allocated now: %d bytes\n", m_allocatedMemory);
	m_gcThreshold = m_allocatedPointers.size() * 2;
	m_gcThreshold = m_gcThreshold < GC_MIN_THRESHOLD ? GC_MIN_THRESHOLD : m_gcThreshold;
	//printf("Adjusting collection threshold to %d\n", m_gcThreshold);
}

void MemoryManager::DebugHeapPrint()
{
	printf("Current allocated memory in bytes: %d\nCurrent object gc count: %d\n", m_allocatedMemory, m_gcThreshold);

}


bool IsPointer(VMObject &o)
{
	return o.type == ObjectType::CHAR_PTR || o.type == ObjectType::DOUBLE_PTR || o.type == ObjectType::INTEGER_PTR;
}