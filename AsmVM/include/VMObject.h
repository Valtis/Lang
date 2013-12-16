#pragma once
enum class ObjectType { UNINITIALIZED, INTEGER, INTEGER_PTR, DOUBLE, DOUBLE_PTR, CHAR, CHAR_PTR };

template <typename T>
struct Ptr
{
	T *ptr;
	bool gc_marked;
};

union Values
{
	int integer_value;
	double double_value;
	Ptr<int> int_ptr;
	Ptr<double> double_ptr;

};

struct VMObject
{
	VMObject();

	ObjectType type;
	Values values;
};