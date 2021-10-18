#pragma once
#include "Demo.h"

class ADemoOfBrackets : public ADemo
{
public:

    ADemoOfBrackets();

    virtual void BeginPlay() override;

    virtual ~ADemoOfBrackets() override;

private:

    String brackets;

    TArray<char> properBrackets;

    bool IsStringValid();

    EBracketsSituation PutChar(const char& inChar, TStack<char>* inStack);
    
    EBracketsSituation CheckBrackets(String& outOverflowedBrackets);

    char PairedLeftBracket(const char& inChar) const;

    bool IsRightBracket(const char& inChar) const;
};
