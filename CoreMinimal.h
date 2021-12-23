#pragma once

#include "Enums/EnumLibrary.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <Windows.h>

#pragma region STDTypes

using cstring = char*;
using ccstring = const char*;
using uint = unsigned int;
using uint16 = unsigned short;
using uint32 = uint;
using uint64 = unsigned long;
using int16 = short;
using int32 = int;
using int64 = long;
using String = std::string;
using StringStream = std::stringstream;
using Ostream = std::ostream;
using Istream = std::istream;
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

#define S_PRIVATE(variable) private:\
								variable;\
                            public:\

#define S_PROTECTED(variable) protected:\
								variable;\
                              public:
                               
#define C_PROTECTED(variable) protected:\
								variable;\
                              private:\

#define C_PUBLIC(variable) public:\
							variable;\
                           private:\

#pragma endregion AccessMacros

#pragma region EnumTypes

typedef ETraversalMethod ESortMethod;
#define HighToLow Sequential
#define LowToHigh Inverted

#pragma endregion EnumTypes

#pragma region StandardDatas

namespace StdEPS
{
    const float floatEPS = 1e-2f;
    const double doubleEPS = 1e-4;
}

#define EOS '\0'
#define NOT_FOUND -1
#define PI (3.1415926)
#define HALF_PI (PI / 2)
#define THREE_SECONDS_PI (PI * 3. / 2)

#define Self (*this)

#pragma endregion StandardDatas

#pragma region Strings

#define TO_STRING(x) #x
#define CAT(x, y) x ## y

#pragma endregion Strings

#pragma region BinaryTree



#pragma endregion BinaryTree

#pragma region Exception

struct ExceptionChecker
{
	static void Throw(bool inBoolean)
	{
		if (!inBoolean)
		{
			throw inBoolean;
		}
	}
		
};

#define CHECK(inBoolean)\
	try\
	{\
		ExceptionChecker::Throw((inBoolean));\
	}\

#pragma endregion Exception