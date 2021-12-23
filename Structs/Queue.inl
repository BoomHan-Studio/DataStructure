#pragma once
#include "Queue.h"
#include "FunctionLibrarys/DataHandleStatics.h"
#include "FunctionLibrarys/DebugStatics.h"
#define QUEUE_MAX_SIZE 1000

template <typename T>
TQueue<T>::TQueue(uint32 inMaxSize)
	:MaxSize(UDataHandleStatics::Clamp(inMaxSize, 1, QUEUE_MAX_SIZE)),
	queueArray(new T[MaxSize]),
	currentElements(0),
	front(0),
	rear(0)
{
	
}

FORCEINLINE void HandleFrontRear(uint32& inValue, const uint32& inMaxSize)
{
	inValue = (inValue + 1) % inMaxSize;
}

template <typename T>
void TQueue<T>::Enqueue(const T& inValue)
{
	try
	{
		CheckIfFull();
	}
	catch (bool)
	{
		UDebugStatics::ExceptionWarning("Queue.inl", "Enqueue");
	}
	queueArray[rear] = inValue;
	HandleFrontRear(rear, MaxSize);
	currentElements++;
}

template <typename T>
T TQueue<T>::Dequeue()
{
	try
	{
		CheckIfEmpty();
	}
	catch (bool)
	{
		UDebugStatics::ExceptionWarning("Queue.inl", "Dequeue");
	}
	T copy = queueArray[front];
	HandleFrontRear(front, MaxSize);
	currentElements--;
	return copy;
}

template <typename T>
T& TQueue<T>::Front()
{
	try
	{
		CheckIfEmpty();
	}
	catch (bool)
	{
		UDebugStatics::ExceptionWarning("Queue.inl", "Front");
	}
	return queueArray[front];
}

template <typename T>
void TQueue<T>::ForceClear()
{
	front = rear = 0;
}

template <typename T>
uint32 TQueue<T>::GetCurrentSize() const noexcept
{
	return currentElements;
}

template <typename T>
bool TQueue<T>::Empty() const noexcept
{
	return (!currentElements);
}

template <typename T>
TQueue<T>::operator bool() const noexcept
{
	return (!Empty());
}

template <typename T>
bool TQueue<T>::Full() const noexcept
{
	return (currentElements == MaxSize);
}

template <typename T>
void TQueue<T>::CheckIfEmpty() const
{
	const bool isEmpty = Empty();
	if (isEmpty)
	{
		throw isEmpty;
	}
}

template <typename T>
void TQueue<T>::CheckIfFull() const
{
	const bool isFull = Full();
	if (isFull)
	{
		throw isFull;
	}
}

template <typename T>
TQueue<T>::~TQueue()
{
	delete[] queueArray;
	currentElements = 0;
	front = 0;
	rear = 0;
}
