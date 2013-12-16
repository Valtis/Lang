#pragma once
#include <list>

#include "VMObject.h"
class VM;



class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();

	VMObject Allocate(VM *vm, ObjectType type, int cnt);

	bool MustCollect() { return m_allocatedPointers.size() >= m_gcThreshold;  }
	void RunGC(VM *vm);

private:

	bool IsPointer(VMObject &o);

	int m_gcThreshold;
	long int m_allocatedMemory;
	

	std::list<Ptr *> m_allocatedPointers;
};