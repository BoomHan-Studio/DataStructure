#ifndef COREMINIMAL
#define COREMINIMAL

#include "Enums/EnumLibrary.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <map>

#pragma region STDTypes

typedef unsigned int uint;
typedef std::string String;
typedef std::stringstream StringStream;
template<typename T1, typename T2>
using TMap = std::map<T1, T2>;

using std::cout;
using std::endl;
using std::cin;
#define Cout cout
#define Endl endl
#define Cin cin

#pragma endregion STDtypes

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

#define FORCEINLINE _forceinline
#define Self (*this)

#endif