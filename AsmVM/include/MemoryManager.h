#pragma once
#include <list>

#include "VMObject.h"
class VM;

bool IsPointer(VMObject &o);


class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();

	VMObject Allocate(VM *vm, ObjectType type, int cnt);

	bool MustCollect() { return m_allocatedPointers.size() >= m_gcThreshold;  }
	void RunGC(VM *vm);

	void DebugHeapPrint();

private:




	int m_gcThreshold;
	long int m_allocatedMemorySizeInBytes;

	std::list<Ptr *> m_allocatedPointers;
};