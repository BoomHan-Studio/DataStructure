#include "Individual.h"
#include "FunctionLibrarys/DataHandleStatics.h"

FIndividual::FIndividual(const double coef, const int expo)
    :Coefficient(coef),
    Exponent(expo)
{
    
}

FIndividual::FIndividual(const FIndividual& another)
    :Coefficient(another.Coefficient),
    Exponent(another.Exponent)
{
    
}

FIndividual::~FIndividual()
{
    Coefficient = 0;
    Exponent = 0;
}

String FIndividual::ToString(bool isSignedIfPositive, char inDisplayChar) const
{
    if (!Coefficient)
    {
        return "0";
    }
    const String symbol = ((Coefficient > 0) ? (isSignedIfPositive ? "+" : "") : "-");
    const String spacedSymbol = (isSignedIfPositive ? ' ' + symbol + ' ' : symbol);
    const double absCoefficient = UDataHandleStatics::Absolution(Coefficient);
    if (!Exponent)
    {
        return (spacedSymbol + UDataHandleStatics::ToStringFromNumber(absCoefficient));
    }
    const String coefStr = (!UDataHandleStatics::IsNearlyEqual(absCoefficient, 1) ? UDataHandleStatics::ToStringFromNumber(absCoefficient) : "");
    String expoStr = ((Exponent != 1) ? '^' + UDataHandleStatics::ToStringFromNumber(Exponent) : "");
    if (Exponent < 0)
    {
        expoStr.insert(expoStr.begin() + 1, '(');
        expoStr.insert(expoStr.end(), ')');
    }
    return (spacedSymbol + coefStr + inDisplayChar + expoStr);
}

bool FIndividual::IsExponentEqualTo(const FIndividual& another) const
{
    return (Exponent == another.Exponent);
}

bool FIndividual::IsExponentLargerThan(const FIndividual& another) const
{
    return (Exponent > another.Exponent);
}

bool FIndividual::IsExponentSmallerThan(const FIndividual& another) const
{
    return (Exponent < another.Exponent);
}

FIndividual& FIndividual::operator=(const FIndividual& another)
{
    Coefficient = another.Coefficient;
    Exponent = another.Exponent;
    return Self;
}

bool FIndividual::operator ==(const FIndividual& another) const
{
    return (UDataHandleStatics::IsNearlyEqual(Coefficient, another.Coefficient) && IsExponentEqualTo(another));
}

bool FIndividual::operator >(const FIndividual& another) const
{
    return IsExponentLargerThan(another);
}

bool FIndividual::operator <(const FIndividual& another) const
{
    return IsExponentSmallerThan(another);
}

bool FIndividual::operator >=(const FIndividual& another) const
{
    return !(Self < another || IsExponentEqualTo(another));
}

bool FIndividual::operator <=(const FIndividual& another) const
{
    return !(Self > another || IsExponentEqualTo(another));
}

FIndividual& FIndividual::operator +=(const FIndividual& another)
{
    if (!IsExponentEqualTo(another))
    {
        return Self;
    }
    Coefficient += another.Coefficient;
    return Self;
}

FIndividual& FIndividual::operator-=(const FIndividual& another)
{
    if (!IsExponentEqualTo(another))
    {
        return Self;
    }
    Coefficient -= another.Coefficient;
    return Self;
}

FIndividual& FIndividual::operator*=(const FIndividual& another)
{
    Coefficient *= another.Coefficient;
    Exponent += another.Exponent;
    return Self;
}

const FIndividual FIndividual::operator+(const FIndividual& another)
{
    FIndividual copy(Self);
    copy += another;
    return copy;
}

const FIndividual FIndividual::operator-(const FIndividual& another)
{
    FIndividual copy(Self);
    copy -= another;
    return copy;
}

const FIndividual FIndividual::operator*(const FIndividual& another)
{
    FIndividual copy(Self);
    copy *= another;
    return copy;
}

EExponentsCompare FIndividual::ExponentCompareWith(const FIndividual& another) const
{
    if (IsExponentLargerThan(another)) return Larger;
    if (IsExponentEqualTo(another)) return Equal;
    return Smaller;
}

void FIndividual::Derivate()
{
    Coefficient *= Exponent;
    Exponent -= 1;
}
