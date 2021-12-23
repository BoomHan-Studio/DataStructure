#include "String.h"
#include "FunctionLibrarys/DebugStatics.h"
#include "FunctionLibrarys/StringStatics.h"

#define ARRANGE_STRING_SIZE(inLen) new char[(inLen) + 1] 
#define HEAD 0
#define TAIR (length + 1)

FString::FString(ccstring inString)
	:length(UStringStatics::StringLength(inString)),
	str(ARRANGE_STRING_SIZE(length))
{
	UStringStatics::StringsCopy(str, inString);
}

FString::FString(const FString& another)
	:length(another.length),
	str(ARRANGE_STRING_SIZE(length))
{
	UStringStatics::StringsCopy(str, another.str);
}

const FString& FString::operator =(const FString& another)
{
	delete[] str;
	length = another.length;
	str = ARRANGE_STRING_SIZE(length);
	UStringStatics::StringsCopy(str, another.ToCStr());
	return Self;
}

const FString& FString::operator +=(const FString& another)
{
	FString copy(str);
	delete[] str;
	str = ARRANGE_STRING_SIZE(length + another.length);
	UStringStatics::StringsCatenate(UStringStatics::StringsCopy(str, copy.ToCStr()), another.ToCStr());
	return Self;
}

FString FString::operator +(const FString& another)
{
	cstring copy = ARRANGE_STRING_SIZE(length + another.Length());
	UStringStatics::StringsCatenate(UStringStatics::StringsCopy(copy, str), another.ToCStr());
	return FString(copy);
}

FString FString::SubString(uint32 inBeginIndex, uint32 inEndIndex)
{
	CHECK((inBeginIndex <= inEndIndex) && (inEndIndex < TAIR))
	catch (bool)
	{
		UDebugStatics::ExceptionWarning("String.cpp", "SubString");
	}
	const uint32 subLength = inEndIndex - inBeginIndex;
	cstring subStr = ARRANGE_STRING_SIZE(subLength);
	for (uint32 i = 0; i < subLength; i++)
	{
		subStr[i] = str[i + inBeginIndex];
	}
	subStr[subLength] = EOS;
	FString result(subStr);
	delete[] subStr;
	return result;
}

uint32 FString::Find(const FString& inTargetString)
{
	uint32 index = length;
	const int32 deltaLength = length - inTargetString.Length();
	if (deltaLength > 0)
	{
		for (uint32 i = 0; i <= uint32(deltaLength); i++)
		{
			if (SubString(i, i + inTargetString.Length()) == inTargetString)
			{
				index = i;
				break;
			}
		}
	}
	else if (!deltaLength)
	{
		if (operator ==(inTargetString))
		{
			index = 0;
		}
	}
	return index;
}

void FString::RemoveByIndexes(uint32 inBeginIndex, uint32 inEndIndex)
{
	CHECK((!((inBeginIndex == 0) && (inEndIndex == TAIR))) && (inBeginIndex <= inEndIndex))
	catch (bool)
	{
		UDebugStatics::ExceptionWarning("String.cpp", "RemoveByIndexes");
	}
	operator =(SubString(0, inBeginIndex) + SubString(inEndIndex, length));
}

void FString::RemoveByLength(uint32 inBeginIndex, uint32 inRemoveLength)
{
	RemoveByIndexes(inBeginIndex, inBeginIndex + inRemoveLength);
}

void FString::Insert(uint32 inBeginIndex, const FString& inString)
{
	cstring former = ARRANGE_STRING_SIZE(inBeginIndex);
	cstring latter = ARRANGE_STRING_SIZE(length - inBeginIndex);
	UStringStatics::StringsCopy(former, SubString(0, inBeginIndex));
	UStringStatics::StringsCopy(latter, SubString(inBeginIndex, length));
	cstring result = ARRANGE_STRING_SIZE(length + inString.Length());
	UStringStatics::StringsCatenate(UStringStatics::StringsCatenate(UStringStatics::StringsCopy(result, former), inString.ToCStr()), latter);
	operator =(FString(result));
}

FString::~FString()
{
	delete[] str;
	length = 0;
}