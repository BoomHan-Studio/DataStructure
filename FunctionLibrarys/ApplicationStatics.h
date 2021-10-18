﻿#pragma once
#include "Statics.h"

class UApplicationStatics : UStatics
{
private:
    /**
    *@brief 此类禁止构造。
    */
    UApplicationStatics()
        :UStatics()
    {
        
    }
public:

    static FORCEINLINE void Pause();

    static FORCEINLINE void ClearScreen();
};

#include "ApplicationStatics.inl"