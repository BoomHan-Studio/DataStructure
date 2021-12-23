#pragma once
#include "Statics.h"

class UDebugStatics : UStatics
{
private:
    /**
     *@brief 此类禁止构造。
     */
    UDebugStatics() = delete;

public:

    /**
     *@brief 放置Debug调试点，输出信息。
     *@param inDebugPointNumber 测试点编号
     *@param inText 调试信息文本
     *@param shouldPause 再放置调试点的时候，是否暂停程序。
     *@note 只会在Debug配置下有效,release下调用将会无事发生。
     */
    static FORCEINLINE void PutDebugPoint(int inDebugPointNumber, const String& inText, bool shouldPause = false);

    static FORCEINLINE void ExceptionWarning(String inFileName, String inFunctionName, int inExitCode = 1);

    template<typename T0, typename ... Ts>
    static void DebugLog(EDebugLevel inLevel, const T0& inElement, const Ts& ... inElements);
    
    template<typename T>
    static FORCEINLINE void DebugLog(EDebugLevel inLevel, const T& inElement);

private:    
    template<typename T0, typename ... Ts>
    static void Print(const T0& inElement, const Ts& ... inElements);

    template<typename T>
    static FORCEINLINE void Print(const T& inElement);

    static TMap<EDebugLevel, uint16> GetColorMap();
};

#include "DebugStatics.inl"