#ifndef COREMINIMAL
#define COREMINIMAL

#include "Enums/EnumLibrary.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

#pragma region AccessMacros

#define S_PRIVATE(variable); private:\
                                variable;\
                             public:\

#define S_PROTECTED(variable); protected:\
                                   variable;\
                               public:
                               
#define C_PROTECTED(variable); protected:\
                                   variable;\
                               private:\

#define C_PUBLIC(variable); public:\
                                variable;\
                            private:\

#pragma endregion AccessMacros

typedef ETraversalMethod ESortMethod;
#define HighToLow Sequential
#define LowToHigh Inverted

namespace StdEPS
{
    const float floatEPS = 1e-4f;
    const double doubleEPS = 1e-8;
}

#define NOT_FOUND -1

#endif