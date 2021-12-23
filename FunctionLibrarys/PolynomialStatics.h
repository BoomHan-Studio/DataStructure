#pragma once
#include "Statics.h"
#include "Classes/Polynomial.h"

class UPolynomialStatics : UStatics
{
private:
	/**
	 *@brief 此类禁止构造。
	 */
    UPolynomialStatics() = delete;
    
public:

    /**
     *
     */
    static FORCEINLINE UPolynomial* PolysPlus(UPolynomial* inPolyA, UPolynomial* inPolyB);

    /**
     *
     */
    static FORCEINLINE UPolynomial* PolysMinus(UPolynomial* inPolyA, UPolynomial* inPolyB);

    /**
     *
     */
    static FORCEINLINE UPolynomial* PolysMultiply(UPolynomial* inPolyA, UPolynomial* inPolyB);

    /**
     *
     */
    static FORCEINLINE UPolynomial* PolyDerivate(UPolynomial* inPoly);
};

#include "PolynomialStatics.inl"