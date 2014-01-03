#pragma once
#include "VM.h"

#include "Instructions\ArithmeticOperationBase.h"

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
		SetType<Type>(o);
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
		SetType<Type>(o);
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
		SetType<Type>(o);
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
		SetType<Type>(o);
		*(Type *)(&o.values) = m_operand1.GetValue(vm) / m_operand2.GetValue(vm);
		vm->m_registers[m_storeRegister] = o;
	}
};