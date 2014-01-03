#pragma once
#include "VMObject.h"

class TypeSetter
{
public:
	template <typename Type>

	static void SetType(VMObject &o)
	{
		// should be handled in specialized methods
		static_assert(false);
	}

	template <>
	static void SetType<int>(VMObject &o)
	{
		o.type = ObjectType::INTEGER;
	}

	template <>
	static void SetType<char>(VMObject &o)
	{
		o.type = ObjectType::CHAR;
	}

	template <>
	static void SetType<double>(VMObject &o)
	{
		o.type = ObjectType::DOUBLE;
	}

};
