#include "MemoryManager.h"
#include <cstdlib>
#include "VM.h"


#define GC_MIN_THRESHOLD 20
MemoryManager::MemoryManager() : m_gcThreshold(20), m_allocatedMemorySizeInBytes(0)
{

}

MemoryManager::~MemoryManager()
{
	for (auto &ptr : m_allocatedPointers)
	{
		free(ptr->ptr);
		free(ptr);
	}
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
	managedPtr->size = cnt*size;
	m_allocatedMemorySizeInBytes += managedPtr->size;
	
	managedPtr->ptr = malloc(size*cnt);
	
	if (managedPtr->ptr == nullptr)
	{
		RunGC(vm);
		managedPtr->ptr = malloc(size*cnt);
		if (managedPtr == nullptr)
		{
			throw std::runtime_error("Memory allocation failed - out of memory?");
		}
	}


	o.type = t;
	o.values.ptr = managedPtr;
	m_allocatedPointers.push_back(managedPtr);

	return o;
}


void MemoryManager::RunGC(VM *vm)
{
	//printf("Running garbage collector: Memory allocated now: %d bytes\n", m_allocatedMemory);
	MarkRegisters(vm);
	MarkStack(vm);
	SweepPointers();

	//printf("After garbage collection: Memory allocated now: %d bytes\n", m_allocatedMemory);
	m_gcThreshold = m_allocatedPointers.size() * 2;
	m_gcThreshold = m_gcThreshold < GC_MIN_THRESHOLD ? GC_MIN_THRESHOLD : m_gcThreshold;
	//printf("Adjusting collection threshold to %d\n", m_gcThreshold);
}


void MemoryManager::MarkRegisters(VM * vm)
{
	for (auto &r : vm->m_registers)
	{

		if (IsPointer(r))
		{
			r.values.ptr->m_marked = true;
		}
	}
}

void MemoryManager::MarkStack(VM * vm)
{
	for (int i = 0; i < vm->m_stack_ptr; ++i)
	{
		if (IsPointer(vm->m_stack[i]))
		{
			vm->m_stack[i].values.ptr->m_marked = true;
		}
	}
}

void MemoryManager::SweepPointers()
{
	auto it = m_allocatedPointers.begin();
	while (it != m_allocatedPointers.end())
	{
		if (!(*it)->m_marked)
		{
			m_allocatedMemorySizeInBytes -= (*it)->size;
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
}



void MemoryManager::DebugHeapPrint()
{
	printf("Current allocated memory in bytes: %d\ncurrent allocated object count:%d\nCurrent gc threshold: %d\n", 
		m_allocatedMemorySizeInBytes, m_allocatedPointers.size(), m_gcThreshold);
}


bool IsPointer(const VMObject &o)
{
	return o.type == ObjectType::CHAR_PTR || o.type == ObjectType::DOUBLE_PTR || o.type == ObjectType::INTEGER_PTR;
}