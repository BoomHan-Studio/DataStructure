#include "Polynomial.h"
#include <iostream>

UPolynomial::UPolynomial(const FIndiArray& inArray, bool shouldSort)
    :individualsArray(inArray)
{
    if (shouldSort)
    {
        Sort();
    }
}

void UPolynomial::Sort()
{
    individualsArray.SortArray(HighToLow);
}

void UPolynomial::PrintF(ETraversalMethod inMethod, char inDisplayChar)
{
    int index = 0;
    individualsArray.ForEach([&](FIndividual indi)->void
    {
        std::cout << indi.ToString((index ? true : false), inDisplayChar);
        index++;
    }, inMethod);
    std::cout << std::endl;
}

void UPolynomial::AddIndividual(const FIndividual& inIndividual)
{
    //std::cout << individualsArray[individualsArray.GetSize() - 1].Exponent << std::endl;
    if (inIndividual.IsExponentSmallerThan(individualsArray[individualsArray.GetSize() - 1]))
    {
        individualsArray.Add(inIndividual);
    }
    else
    {
        
    }
}

bool UPolynomial::IsExponentExists(const FIndividual& inIndividual, int& outFoundIndex, int& outInsertIndex)
{
    outFoundIndex = outInsertIndex = 0;
    auto beginIt = individualsArray.CreateIterator();
    auto endIt = individualsArray.CreateIterator() + (individualsArray.GetSize() - 1);
    for (beginIt.MoveIterator())
    return false;
}
