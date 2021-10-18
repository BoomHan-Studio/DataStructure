#include "DemoOfPolynomial.h"
#include "FunctionLibrarys/PolynomialStatics.h"
#include "FunctionLibrarys/ApplicationStatics.h"

ADemoOfPolynomial::ADemoOfPolynomial()
    :displayPoly1(nullptr),
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
    UApplicationStatics::ClearScreen();
    Cout << "多项式A:" << displayPoly1->ToString(HighToLow, displayChar) << Endl;
    Cout << "多项式B:" << displayPoly2->ToString(HighToLow, displayChar) << Endl << Endl;
    UPolynomial* plus = UPolynomialStatics::PolysPlus(displayPoly1, displayPoly2);
    UPolynomial* minus = UPolynomialStatics::PolysMinus(displayPoly1, displayPoly2);
    UPolynomial* multiply = UPolynomialStatics::PolysMultiply(displayPoly1, displayPoly2);
    UPolynomial* derivate1 = UPolynomialStatics::PolyDerivate(displayPoly1);
    UPolynomial* derivate2 = UPolynomialStatics::PolyDerivate(displayPoly2);
    Cout << "A+B=" << plus->ToString(HighToLow, displayChar) << Endl;
    Cout << "A-B=" << minus->ToString(HighToLow, displayChar) << Endl;
    Cout << "A*B=" << multiply->ToString(HighToLow, displayChar) << Endl;
    Cout << "A求导:" << derivate1->ToString(HighToLow, displayChar) << Endl;
    Cout << "B求导:" << derivate2->ToString(HighToLow, displayChar) << Endl;
    delete plus, minus, multiply, derivate1, derivate2;
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
        Cin >> coef;
        Cout << "指数:";
        Cin >> expo;
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
