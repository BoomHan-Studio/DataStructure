// ReSharper disable All
#pragma once
#include "DataHandleStatics.h"

bool UDataHandleStatics::IsNearlyEqual(const float& a, const float& b)
{
    return (Absolution(a - b) < StdEPS::floatEPS);
}

bool UDataHandleStatics::IsNearlyEqual(const double& a, const double& b)
{
    return (Absolution(a - b) < StdEPS::doubleEPS);
}

String UDataHandleStatics::ToStringFromBool(bool inBool, String stringIfTrue, String stringIfFalse)
{
    return (inBool ? stringIfTrue : stringIfFalse);
}

template<typename T>
String UDataHandleStatics::ToStringFromNumber(const T& inNumber)
{
    StringStream stream;
    String result;
    stream << inNumber;
    stream >> result;
    return result;
}

template <typename T>
T UDataHandleStatics::ToNumberFromString(String inString)
{
	StringStream stream;
	T result;
	stream << inString;
	stream >> result;
	return result;
}

template<typename T>
T UDataHandleStatics::Absolution(const T& inNumber)
{
    return (inNumber * (inNumber >= 0 ? 1 : -1));
}

template <typename T>
T& UDataHandleStatics::Max(const T& inA, const T& inB)
{
	const T& result = (inA > inB) ? inA : inB;
	return const_cast<T&>(result);
}

template <typename T>
T& UDataHandleStatics::Max(T&& inA, T&& inB)
{
	return (inA > inB) ? inA : inB;
}

double UDataHandleStatics::Tan(const double& inNumber)
{
    return tan(inNumber);
}

double UDataHandleStatics::ATan(const double& inNumber)
{
    return atan(inNumber);
}

template<typename T>
bool UDataHandleStatics::IsValueBetweenAnd(const T& inNumber, const T& inMin, const T& inMax, bool isLeftInclusive, bool isRightInclusive)
{
    const bool largerThanMin = (isLeftInclusive ? (inNumber >= inMin) : (inNumber > inMin));
    const bool smallerThanMax = (isRightInclusive ? (inNumber <= inMax) : (inNumber < inMax));
    return (largerThanMin && smallerThanMax);
}

template<typename T>
void UDataHandleStatics::Swap(T* inA, T* inB)
{
    if ((!inA) || (!inB))
    {
        return;
    }
    T temp = *inA;
    *inA = *inB;
    *inB = temp;
}

template <typename T0, typename T>
T UDataHandleStatics::Clamp(T0 inValue, T inMin, T inMax)
{
	if (inValue < inMin) inValue = inMin;
	if (inValue > inMax) inValue = inMax;
	return inValue;
}

template <typename T>
void UDataHandleStatics::Delete(const T* inPtr)
{
    if (inPtr)
    {
        delete inPtr;
    }
}

template<typename T>
void UDataHandleStatics::InputNumber(T& outInputValue)
{
    double temp;
    Cin >> temp;
    outInputValue = T(temp);
    Cin.get();
}

void UDataHandleStatics::InputChar(char& outInputChar)
{
	String input;
	cin >> input;
	outInputChar = (input.size() == 1) ? input[0] : ' ';
	cin.get();
}
