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
    const std::string coefStr = UDataHandleStatics::PurifyDecimal(Coefficient != 1 ? std::to_string(Coefficient) : "");
    const std::string expoStr = (Exponent != 1 ? '^' + std::to_string(Exponent) : "");
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

bool FIndividual::operator==(const FIndividual& another)
{
    return (UDataHandleStatics::IsNearlyEqual(Coefficient, another.Coefficient) && IsExponentEqualTo(another));
}

bool FIndividual::operator>(const FIndividual& another)
{
    return IsExponentLargerThan(another);
}

bool FIndividual::operator<(const FIndividual& another)
{
    return IsExponentSmallerThan(another);
}
