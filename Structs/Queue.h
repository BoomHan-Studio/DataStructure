#pragma once
#include "CoreMinimal.h"
#define QUEUE_IDEAL_SIZE 20

template<typename T>
struct TQueue
{
	const uint32 MaxSize;
	S_PRIVATE(T* queueArray);
	S_PRIVATE(uint32 currentElements);
	S_PRIVATE(uint32 front);
	S_PRIVATE(uint32 rear);

	explicit TQueue(uint32 inMaxSize = QUEUE_IDEAL_SIZE);

	TQueue(const TQueue&) = delete;
	const TQueue& operator = (const TQueue&) = delete;

	~TQueue();

	void Enqueue(const T& inValue);

	T Dequeue();

	T& Front();

	FORCEINLINE void ForceClear();

	FORCEINLINE uint32 GetCurrentSize() const noexcept;

	FORCEINLINE bool Empty() const noexcept;

	FORCEINLINE operator bool() const noexcept;

	FORCEINLINE bool Full() const noexcept;

private:	
	void CheckIfEmpty() const;

	void CheckIfFull() const;
};

#include "Queue.inl"