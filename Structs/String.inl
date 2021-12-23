#pragma once
#include "String.h"
#include "FunctionLibrarys/DebugStatics.h"
#include "FunctionLibrarys/StringStatics.h"

ccstring FString::ToCStr() const noexcept
{
	return str;
}

uint32 FString::Length() const noexcept
{
	return length;
}

FString::operator ccstring() const noexcept
{
	return ToCStr();
}

bool FString::operator ==(const FString& another) const
{
	return operator ==(another.ToCStr());
}

bool FString::operator ==(ccstring another) const
{
	return (UStringStatics::StringsCompare(str, another) == 0);
}

bool FString::operator >(const FString& another) const
{
	return operator >(another.ToCStr());
}

bool FString::operator >(ccstring another) const
{
	return (UStringStatics::StringsCompare(str, another) > 0);
}

bool FString::operator<(const FString& another) const
{
	return operator <(another.ToCStr());
}

bool FString::operator <(ccstring another) const
{
	return (UStringStatics::StringsCompare(str, another) < 0);
}

bool FString::operator !=(const FString& another) const
{
	return !operator ==(another);
}

bool FString::operator !=(ccstring another) const
{
	return !operator ==(another);
}

char& FString::operator [](uint32 inIndex) const
{
	CHECK(inIndex < length)
	catch (bool)
	{
		UDebugStatics::ExceptionWarning("String.inl", "operator [] const");
	}
	return str[inIndex];
}

char& FString::operator [](uint32 inIndex)
{
	return static_cast<cstring&>(const_cast<FString&>(Self).str)[inIndex];
}