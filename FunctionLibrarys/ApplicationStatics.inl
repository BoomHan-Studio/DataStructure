#pragma once
#include "ApplicationStatics.h"
#include <cstdlib>

FORCEINLINE void UApplicationStatics::Pause()
{
    system("pause");
}

FORCEINLINE void UApplicationStatics::ClearScreen()
{
    system("cls");
}
