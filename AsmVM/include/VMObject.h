#pragma once
enum class ObjectType { UNINITIALIZED, INTEGER, INTEGER_PTR, DOUBLE, DOUBLE_PTR, CHAR, CHAR_PTR };

struct Ptr
{
	void *ptr;
	bool gc_marked;
};

union Values
{
	int integer_value;
	double double_value;
	char char_value;
	Ptr ptr;

};

struct VMObject
{
	VMObject();

	

	ObjectType type;
	Values values;
};