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
    for (auto it = individualsArray.CreateIterator(); it.IsValid(); it.MoveIterator(Sequential))
    {
        
    }
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
    individualsArray.Add(inIndividual);
}
