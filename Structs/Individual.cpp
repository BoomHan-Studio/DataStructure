#include "Individual.h"
#include "FunctionLibrarys/DataHandleStatics.h"

FIndividual::FIndividual(const double coef, const int expo)
    :Coefficient(coef),
    Exponent(expo)
{
    
}

FIndividual::~FIndividual()
{
    Coefficient = 0;
    Exponent = 0;
}

std::string FIndividual::ToString(bool isSignedIfPositive, char inDisplayChar) const
{
    if (!Coefficient)
    {
        return "";
    }
    const std::string symbol = (isSignedIfPositive) ? "+" : "";
    if (!Exponent)
    {
        return (symbol + UDataHandleStatics::ToStringFromNumber(Coefficient));
    }
    const std::string coefStr = (!UDataHandleStatics::IsNearlyEqual(Coefficient, 1) ? UDataHandleStatics::ToStringFromNumber(Coefficient) : "");
    const std::string expoStr = ((Exponent != 1) ? '^' + UDataHandleStatics::ToStringFromNumber(Exponent) : "");
    return (symbol + coefStr + inDisplayChar + expoStr);
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
    return !((*this) < another || IsExponentEqualTo(another));
}

bool FIndividual::operator <=(const FIndividual& another) const
{
    return !((*this) > another || IsExponentEqualTo(another));
}
