#include "DemoOfBrackets.h"
#define ILLEGAL 'N'

ADemoOfBrackets::ADemoOfBrackets()
{
    demoName = "括号配对检验";
    properBrackets.Add('[', ']', '(', ')', '{', '}');
}

void ADemoOfBrackets::BeginPlay()
{
    ADemo::BeginPlay();
    Cout << "请输入括号字符串:";
    std::getline(Cin, brackets);
    if (!IsStringValid())
    {
        Cout << "出现不合法字符!" << Endl;
        return;
    }
    String overflowedBrackets;
    switch (CheckBrackets(overflowedBrackets))
    {
    case Valid:
        Cout << "括号配对。" << Endl;
        break;
    case LeftOverflow:
        Cout << "括号不配对，左边溢出" << overflowedBrackets << Endl;
        break;
    case RightOverflow:
        Cout << "括号不配对，右边溢出" << overflowedBrackets << Endl;
        break;
    }
}

bool ADemoOfBrackets::IsStringValid()
{
    if (brackets.empty())
    {
        return false;
    }
    for (auto it = brackets.begin(); it != brackets.end(); ++it)
    {
        if (!properBrackets.Contains(*it))
        {
            return false;
        }
    }
    return true;
}

EBracketsSituation ADemoOfBrackets::CheckBrackets(String& outOverflowedBrackets)
{
    UDebugStatics::PutDebugPoint(1, "执行CheckBrackets函数");
    outOverflowedBrackets = "";
    TStack<char> charStack(uint(brackets.size()));
    EBracketsSituation result = Valid;
    for (auto it = brackets.begin(); it != brackets.end(); ++it)
    {
        UDebugStatics::PutDebugPoint(2, "进入for循环");
        result = PutChar(*it, &charStack);
        if (result != Valid)
        {
            break;
        }
    }
    if (!charStack.Empty())
    {
        result = LeftOverflow;
    }
    return result;
}

EBracketsSituation ADemoOfBrackets::PutChar(const char& inChar, TStack<char>* inStack)
{
    if (!IsRightBracket(inChar))
    {
        inStack->PushStack(inChar);
        UDebugStatics::PutDebugPoint(3, "是左括号");
        return Valid;
    }
    //右括号
    if (inStack->Empty())
    {
        UDebugStatics::PutDebugPoint(4, "右括号，栈空，返回右端溢出");
        return RightOverflow;
    }
    if (inStack->Top() == PairedLeftBracket(inChar))
    {
        UDebugStatics::PutDebugPoint(5, "右括号，栈不空，若上一个括号与其配对则出栈");
        inStack->Pop();
        return Valid;
    }
    UDebugStatics::PutDebugPoint(6, "返回左端溢出");
    return LeftOverflow;
}

char ADemoOfBrackets::PairedLeftBracket(const char& inChar) const
{
    switch (inChar)
    {
    case ']':return '[';
    case ')':return '(';
    case '}':return '{';
    default:return ILLEGAL;
    }
}

bool ADemoOfBrackets::IsRightBracket(const char& inChar) const
{
    return ((inChar == ']') || (inChar == '}') || (inChar == ')'));
}

ADemoOfBrackets::~ADemoOfBrackets()
{
    brackets = "";
    properBrackets.ClearArray();
}