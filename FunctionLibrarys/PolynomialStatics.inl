#pragma once
#include "PolynomialStatics.h"

FORCEINLINE UPolynomial* UPolynomialStatics::PolysPlus(UPolynomial* inPolyA, UPolynomial* inPolyB)
{
    UPolynomial* result = new UPolynomial(*inPolyA);
    return &result->Plus(*inPolyB);
}

FORCEINLINE UPolynomial* UPolynomialStatics::PolysMinus(UPolynomial* inPolyA, UPolynomial* inPolyB)
{
    UPolynomial* result = new UPolynomial(*inPolyA);
    return &result->Minus(*inPolyB);
}

FORCEINLINE UPolynomial* UPolynomialStatics::PolysMultiply(UPolynomial* inPolyA, UPolynomial* inPolyB)
{
    UPolynomial* result = new UPolynomial(*inPolyA);
    return &result->Multiply(*inPolyB);
}

FORCEINLINE UPolynomial* UPolynomialStatics::PolyDerivate(UPolynomial* inPoly)
{
    return new UPolynomial(inPoly->GetDerivated());
}