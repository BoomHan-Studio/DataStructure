#pragma once
#include "Stack.h"
#include "FunctionLibrarys/DataHandleStatics.h"
#pragma warning(disable:4018)

template <typename T>
TStack<T>::TStack(uint32 inMaxSize)
	:StackSize(UDataHandleStatics::Clamp(inMaxSize, 1, 1000)),
	stackArray(new T[inMaxSize]),
	currentElements(0)
{
	
}

template <typename T>
void TStack<T>::PushStack(const T& inValue)
{
	try
	{
		CheckIfFull();
	}
	catch (uint32)
	{
		UDebugStatics::ExceptionWarning("Stack.inl", "PushStack", 1);
	}
	stackArray[currentElements] = inValue;
	currentElements++;
}

template <typename T>
bool TStack<T>::Empty() const noexcept
{
	return !(currentElements);
}

template <typename T>
T& TStack<T>::Top()
{
	try
	{
		CheckIfEmpty();
	}
	catch (uint32)
	{
		UDebugStatics::ExceptionWarning("Stack.inl", "Top", 1);
	}
	return stackArray[currentElements - 1];
}

template <typename T>
T TStack<T>::Pop()
{
	T& topRef = Top();
	T top = topRef;
	topRef = T(0);
	currentElements--;
	return top;
}

template <typename T>
TStack<T>::operator bool() const noexcept
{
	return !Empty();
}

template <typename T>
void TStack<T>::CheckIfFull() const
{
	if (currentElements >= StackSize)
	{
		throw currentElements;
	}
}

template <typename T>
void TStack<T>::CheckIfEmpty() const
{
	if (Empty())
	{
		throw currentElements;
	}
}

template <typename T>
TStack<T>::~TStack()
{
	delete[] stackArray;
	currentElements = 0;
}
