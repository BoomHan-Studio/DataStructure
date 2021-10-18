#pragma once
#include "Statics.h"

class UDebugStatics : UStatics
{
private:
    /**
    *@brief 此类禁止构造。
    */
    UDebugStatics()
        :UStatics()
    {
        
    }

public:

    static FORCEINLINE void PutDebugPoint(int inDebugPointNumber, const String& inText, bool shouldPause = false);
};

#include "DebugStatics.inl"