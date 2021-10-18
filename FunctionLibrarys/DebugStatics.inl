#pragma once
#include "ApplicationStatics.h"
#include "DebugStatics.h"
#include "DataHandleStatics.h"

FORCEINLINE void UDebugStatics::PutDebugPoint(int inDebugPointNumber, const String& inText, bool shouldPause)
{
#if _DEBUG
    const String text = "---测试点" + UDataHandleStatics::ToStringFromNumber(inDebugPointNumber) + ":" + inText + "---";
    Cout << text << Endl;
    if (shouldPause)
    {
        UApplicationStatics::Pause();
    }
#endif
}
