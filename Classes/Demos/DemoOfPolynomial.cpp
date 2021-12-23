#include "DemoOfPolynomial.h"
#include "FunctionLibrarys/PolynomialStatics.h"
#include "FunctionLibrarys/ApplicationStatics.h"

ADemoOfPolynomial::ADemoOfPolynomial()
    :ADemo(),
	displayPoly1(nullptr),
    displayPoly2(nullptr)
{
    demoName = "多项式运算";
}

void ADemoOfPolynomial::BeginPlay()
{
    ADemo::BeginPlay();
    Cout << "请选择多项式的展示字母(默认为x):";
    char displayChar;
    Cin >> displayChar;
    auto CreationProgress = [&](char polyName)->void
    {
        UApplicationStatics::ClearScreen();
        Cout << "现在开始创建多项式" << polyName << "。" << Endl;
        if (polyName == 'A') CreatePolynomial(displayPoly1);
        else CreatePolynomial(displayPoly2);
    };
    CreationProgress('A');
    CreationProgress('B');
    DisplayPolys(displayChar);
    ChangePoly(displayChar);
}

void InitPolyNumber(int& outPolyNumber)
{
    Cout << "请输入多项式的项数:";
    Cin >> outPolyNumber;
    if (outPolyNumber < 0)
    {
        throw outPolyNumber;
    }
}

void ADemoOfPolynomial::ChangePoly(char inDisplayChar)
{
    Cout << "现在开始对多项式进行修改。";
    while (1)
    {
        Cout << "是否需要修改多项式?(A/B/N)";
        char reply;
        Cin >> reply;
        Cin.get();
        if (reply == 'N')
        {
            break;
        }
        if ((reply != 'A') && (reply != 'B'))
        {
            continue;
        }
        UPolynomial* targetPoly = (reply == 'A' ? displayPoly1 : displayPoly2);
        int num;
        Cout << "修改多项式" << reply << "的第几项?(如果越界则会做求余处理)";
        UDataHandleStatics::InputNumber(num);
        FIndividual& targetIndi = targetPoly->individualsArray[num - 1];
        double coef;
        int expo;
        Cout << "正在修改第" << targetPoly->individualsArray.ToRealIndex(num) << "项" << Endl << "系数:";
        UDataHandleStatics::InputNumber(coef);
        Cout << "指数:";
        UDataHandleStatics::InputNumber(expo);
        targetIndi = FIndividual(coef, expo);
        targetPoly->Sort();
    }
    DisplayPolys(inDisplayChar);
}

void ADemoOfPolynomial::DisplayPolys(char inDisplayChar)
{
    UApplicationStatics::ClearScreen();
    Cout << "多项式A:" << displayPoly1->ToString(HighToLow, inDisplayChar) << Endl;
    Cout << "多项式B:" << displayPoly2->ToString(HighToLow, inDisplayChar) << Endl << Endl;
    UPolynomial* plus = UPolynomialStatics::PolysPlus(displayPoly1, displayPoly2);
    UPolynomial* minus = UPolynomialStatics::PolysMinus(displayPoly1, displayPoly2);
    UPolynomial* multiply = UPolynomialStatics::PolysMultiply(displayPoly1, displayPoly2);
    UPolynomial* derivate1 = UPolynomialStatics::PolyDerivate(displayPoly1);
    UPolynomial* derivate2 = UPolynomialStatics::PolyDerivate(displayPoly2);
    Cout << "A+B=" << plus->ToString(HighToLow, inDisplayChar) << Endl;
    Cout << "A-B=" << minus->ToString(HighToLow, inDisplayChar) << Endl;
    Cout << "A*B=" << multiply->ToString(HighToLow, inDisplayChar) << Endl;
    Cout << "A求导:" << derivate1->ToString(HighToLow, inDisplayChar) << Endl;
    Cout << "B求导:" << derivate2->ToString(HighToLow, inDisplayChar) << Endl;
    delete plus, minus, multiply, derivate1, derivate2;
}

void ADemoOfPolynomial::CreatePolynomial(UPolynomial*& outPolynomial)
{
    if (outPolynomial)
    {
        return;
    }
    outPolynomial = new UPolynomial();
    int polyNumber;
    try
    {
        InitPolyNumber(polyNumber);
    }
    catch (int)
    {
        Cout << "Exception in DemoOfPolynomial.cpp : CreatePolynomial()";
        exit(1);
    }
    while (polyNumber--)
    {
        system("cls");
        double coef;
        int expo;
        outPolynomial->PrintF(HighToLow);
        Cout << "系数:";
        UDataHandleStatics::InputNumber(coef);
        Cout << "指数:";
        UDataHandleStatics::InputNumber(expo);
        outPolynomial->AddIndividual(coef, expo);
    }
    Cout << "已成功创建多项式:";
    outPolynomial->PrintF(HighToLow);
    UApplicationStatics::Pause();
}

ADemoOfPolynomial::~ADemoOfPolynomial()
{
    delete displayPoly1, displayPoly2;
}
