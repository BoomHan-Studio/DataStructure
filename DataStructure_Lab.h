#pragma once
#include "Classes/Polynomial.h"
#include "Core.h"
#include "Classes/Demos/DemoOfPolynomial.h"
#include "Classes/Demos/DemoOfBrackets.h"

class ADemoCreator
{
    using CreationFunction = ADemo* (ADemoCreator::*)();
    
    TMap<int, CreationFunction> creationMap;

    TArray<int> demosArray;
public:
    
    ADemoCreator()
        :demosArray(TArray<int>())
    {
        creationMap.insert_or_assign(1, &ADemoCreator::CreateDemoOfPolynomial);
        creationMap.insert_or_assign(2, &ADemoCreator::CreateDemoOfBrackets);
    }

    void ShowDemosList()
    {
        Cout << "1.多项式运算" << Endl;
        Cout << "2.括号匹配检验" << Endl;

        Cout << "请选择你的英雄:";
    }
    
    ADemo* CreateDemo(int inCommand)
    {
        if (demosArray.Contains(inCommand) || creationMap.find(inCommand) == creationMap.end())
        {
            return nullptr;
        }
        demosArray.Add(inCommand);
        auto executedFunction = creationMap[inCommand];
        return (this->*executedFunction)();
    }

private:

    ADemo* CreateDemoOfPolynomial()
    {
        return new ADemoOfPolynomial();
    }

    ADemo* CreateDemoOfBrackets()
    {
        return new ADemoOfBrackets();
    }
};

#ifdef COREMINIMAL
using namespace std;
#endif