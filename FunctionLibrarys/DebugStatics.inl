#pragma once
#include "ApplicationStatics.h"
#include "DebugStatics.h"
#include "DataHandleStatics.h"
#include <Windows.h>

#if _DEBUG

FORCEINLINE void UDebugStatics::PutDebugPoint(int inDebugPointNumber, const String& inText, bool shouldPause)
{
    const String text = "---测试点" + UDataHandleStatics::ToStringFromNumber(inDebugPointNumber) + ":" + inText + "---";
    Cout << text << Endl;
    if (shouldPause)
    {
        UApplicationStatics::Pause();
    }
}

FORCEINLINE void UDebugStatics::ExceptionWarning(String inFileName, String inFunctionName, int inExitCode)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    Cout << "Exception in " + inFileName + " : " + inFunctionName + "!" << Endl;
    exit(inExitCode);
}

template <typename T0, typename ... Ts>
void UDebugStatics::DebugLog(EDebugLevel inLevel, const T0& inElement, const Ts&... inElements)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | GetColorMap()[inLevel]);
    Print(inElement);
    Print(inElements ...);
    cout << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

template <typename T>
FORCEINLINE void UDebugStatics::DebugLog(EDebugLevel inLevel, const T& inElement)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | GetColorMap()[inLevel]);
    Print(inElement);
    cout << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

template <typename T0, typename ... Ts>
void UDebugStatics::Print(const T0& inElement, const Ts&... inElements)
{
    Print(inElement);
    Print(inElements ...);
}

template <typename T>
FORCEINLINE void UDebugStatics::Print(const T& inElement)
{
    cout << inElement;
}

FORCEINLINE TMap<EDebugLevel, uint16> UDebugStatics::GetColorMap()
{
    return TMap<EDebugLevel, uint16>{{Log, FOREGROUND_GREEN}, {Warning, FOREGROUND_RED | FOREGROUND_GREEN}, {Error, FOREGROUND_RED}};
}

























#else

FORCEINLINE void UDebugStatics::PutDebugPoint(int inDebugPointNumber, const String& inText, bool shouldPause){}
FORCEINLINE void UDebugStatics::ExceptionWarning(String inFileName, String inFunctionName, int inExitCode){}
template <typename T0, typename ... Ts>
void UDebugStatics::DebugLog(EDebugLevel inLevel, const T0& inElement, const Ts&... inElements){}
template <typename T>
FORCEINLINE void UDebugStatics::DebugLog(EDebugLevel inLevel, const T& inElement){}
template <typename T0, typename ... Ts>
void UDebugStatics::Print(const T0& inElement, const Ts&... inElements){}
template <typename T>
FORCEINLINE void UDebugStatics::Print(const T& inElement){}
FORCEINLINE TMap<EDebugLevel, uint16> UDebugStatics::GetColorMap(){return TMap<EDebugLevel, uint16>();}

#endif