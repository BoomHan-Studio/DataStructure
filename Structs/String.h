#pragma once
#include "CoreMinimal.h"

struct FString
{
	S_PROTECTED(uint32 length);
	
	S_PROTECTED(cstring str);

	FString(ccstring inString = nullptr);

	FString(const FString& another);

	FORCEINLINE ccstring ToCStr() const noexcept;

	FORCEINLINE uint32 Length() const noexcept;

	FORCEINLINE operator ccstring() const noexcept;

	const FString& operator =(const FString& another);

	const FString& operator +=(const FString& another);

	FString operator +(const FString& another);

	FORCEINLINE bool operator ==(const FString& another) const;

	FORCEINLINE bool operator ==(ccstring another) const;

	FORCEINLINE bool operator >(const FString& another) const;

	FORCEINLINE bool operator >(ccstring another) const;

	FORCEINLINE bool operator <(const FString& another) const;

	FORCEINLINE bool operator <(ccstring another) const;

	FORCEINLINE bool operator !=(const FString& another) const;

	FORCEINLINE bool operator !=(ccstring another) const;

	FORCEINLINE char& operator [](uint32 inIndex) const;

	FORCEINLINE char& operator [](uint32 inIndex);

	FString SubString(uint32 inBeginIndex, uint32 inEndIndex);

	uint32 Find(const FString& inTargetString);

	void RemoveByLength(uint32 inBeginIndex, uint32 inRemoveLength);

	void RemoveByIndexes(uint32 inBeginIndex, uint32 inEndIndex);

	void Insert(uint32 inBeginIndex, const FString& inString);
	
	~FString();

private:
	
};

#include "String.inl"