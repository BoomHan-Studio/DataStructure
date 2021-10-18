#pragma once
#include "Demo.h"
#include "Classes/Polynomial.h"

class ADemoOfPolynomial : public ADemo
{
public:
    ADemoOfPolynomial();

    virtual void BeginPlay() override;

    virtual ~ADemoOfPolynomial() override;

private:

    void CreatePolynomial(UPolynomial*& outPolynomial);

    UPolynomial* displayPoly1;

    UPolynomial* displayPoly2;
};
