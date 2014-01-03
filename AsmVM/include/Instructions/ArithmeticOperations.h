#pragma once

#include "VM.h"
#include "Instructions/ArithmeticOperationBase.h"
#include "Instructions/TypeSetters.h"

template <typename Type>
class Addition : public ArithmeticOperationBase<Type, Addition<Type>>
{
public:
	Addition(Operand<Type> operand1, Operand<Type> operand2, int storeRegister) :
		ArithmeticOperationBase(operand1, operand2, storeRegister)
	{

	}

	void Execute(VM *vm)
	{
		VMObject o;
		TypeSetter::SetType<Type>(o);
		*(Type *)(&o.values) = m_operand1.GetValue(vm) + m_operand2.GetValue(vm);
		vm->m_registers[m_storeRegister] = o;
	}
};

template <typename Type>
class Substraction : public ArithmeticOperationBase<Type, Substraction<Type>>
{
public:
	Substraction(Operand<Type> operand1, Operand<Type> operand2, int storeRegister) :
		ArithmeticOperationBase(operand1, operand2, storeRegister)
	{

	}

	void Execute(VM *vm)
	{
		VMObject o;
		TypeSetter::SetType<Type>(o);
		*(Type *)(&o.values) = m_operand1.GetValue(vm) - m_operand2.GetValue(vm);
		vm->m_registers[m_storeRegister] = o;
	}
};

template <typename Type>
class Multiplication : public ArithmeticOperationBase<Type, Multiplication<Type>>
{
public:
	Multiplication(Operand<Type> operand1, Operand<Type> operand2, int storeRegister) :
		ArithmeticOperationBase(operand1, operand2, storeRegister)
	{

	}

	void Execute(VM *vm)
	{
		VMObject o;
		TypeSetter::SetType<Type>(o);
		*(Type *)(&o.values) = m_operand1.GetValue(vm) * m_operand2.GetValue(vm);
		vm->m_registers[m_storeRegister] = o;
	}
};


template <typename Type>
class Division : public ArithmeticOperationBase<int, Division<Type>>
{
public:
	Division(Operand<Type> operand1, Operand<Type> operand2, int storeRegister) :
		ArithmeticOperationBase(operand1, operand2, storeRegister)
	{

	}

	void Execute(VM *vm)
	{
		VMObject o;
		TypeSetter::SetType<Type>(o);

		if (m_operand2.GetValue(vm) == 0)
		{
			throw std::runtime_error("Division by zero");
		}

		*(Type *)(&o.values) = m_operand1.GetValue(vm) / m_operand2.GetValue(vm);
		vm->m_registers[m_storeRegister] = o;
	}
};


class RandomizeInteger : public ArithmeticOperationBase<int, RandomizeInteger>
{
public:
	RandomizeInteger(Operand<int> operand1, Operand<int> operand2, int storeRegister) :
		ArithmeticOperationBase(operand1, operand2, storeRegister)
	{

	}

	void Execute(VM *vm)
	{
		VMObject o;
		TypeSetter::SetType<int>(o);
		std::uniform_int_distribution<int> dist(m_operand1.GetValue(vm), m_operand2.GetValue(vm));
		o.values.integer_value = dist(vm->m_generator);
		vm->m_registers[m_storeRegister] = o;
	}
};

class RandomizeDouble : public ArithmeticOperationBase<double, RandomizeDouble>
{
public:
	RandomizeDouble(Operand<double> operand1, Operand<double> operand2, int storeRegister) :
		ArithmeticOperationBase(operand1, operand2, storeRegister)
	{

	}

	void Execute(VM *vm)
	{
		VMObject o;
		TypeSetter::SetType<double>(o);
		std::uniform_real_distribution<double> dist(m_operand1.GetValue(vm), m_operand2.GetValue(vm));
		o.values.double_value = dist(vm->m_generator);
		vm->m_registers[m_storeRegister] = o;
	}
};