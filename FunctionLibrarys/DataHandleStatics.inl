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

String UDataHandleStatics::ToStringFromBool(const bool& inBool)
{
    return (inBool ? "Yes" : "No");
}

template <typename T>
String UDataHandleStatics::ToStringFromNumber(const T& inNumber)
{
    StringStream stream;
    String result;
    stream << inNumber;
    stream >> result;
    return result;
}

template <typename T>
T UDataHandleStatics::Absolution(const T& inNum)
{
    return (inNum * (inNum >= 0 ? 1 : -1));
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

template <typename T>
void UDataHandleStatics::InputNumber(T& outInputValue)
{
    double temp;
    Cin >> temp;
    outInputValue = T(temp);
    Cin.get();
}
