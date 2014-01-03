#pragma once
enum class ObjectType { UNINITIALIZED, INTEGER, INTEGER_PTR, DOUBLE, DOUBLE_PTR, CHAR, CHAR_PTR };


struct Ptr
{
	void *ptr;
	int size;
	bool m_marked;
};

// first value of the union MUST be the value type (eg. first field in Ptr MUST be the value to the pointer)
// Quoting C standard: "A pointer to a union object, suitably converted, points to each of its members" 
// thus the code may make conversions like int a = *(int *)(&VmObject.values);
// for structs, offset of first value is 0; for additional values, paddingf bytes may be inserted.
// as long as the value type is first in any structs that are members of the union, said conversions will work
// and said conversions will be used.
union Values
{
	int integer_value;
	double double_value;
	char char_value;
	Ptr *ptr;
};

struct VMObject
{
	VMObject();


	ObjectType type;
	Values values;
};