#include "Polynomial.h"

UPolynomial::UPolynomial(const FIndiArray& inArray, bool shouldSort)
    :individualsArray(inArray)
{
    if (shouldSort)
    {
        Sort();
    }
}

UPolynomial::UPolynomial()
    :individualsArray()
{
    
}
UPolynomial::UPolynomial(const UPolynomial& another)
    :individualsArray(another.individualsArray)
{
    
}

void UPolynomial::Sort()
{
    individualsArray.SortArray(HighToLow);
}

void UPolynomial::PrintF(ETraversalMethod inMethod, char inDisplayChar)
{
    Cout << ToString(inMethod, inDisplayChar) << Endl;
    //Cout << individualsArray.GetSize() << Endl;
}

void UPolynomial::AddIndividual(const FIndividual& inIndividual)
{
    if (Useless(inIndividual)) return;
    const int size = individualsArray.GetSize();
    if (!size)
    {
        individualsArray.Add(inIndividual);
    }
    else
    {
        (size == 1) ? AddWhenSingle(inIndividual) : AddWhenDuo(inIndividual);
    }
}

void UPolynomial::AddIndividual(double coef, int expo)
{
    AddIndividual(FIndividual(coef, expo));
}

String UPolynomial::ToString(ETraversalMethod inMethod, char inDisplayChar)
{
    int index = 0;
    String result;
    individualsArray.ForEach([&](FIndividual indi)->void
    {
        result += indi.ToString((index ? true : false), inDisplayChar);
        index++;
    }, inMethod);
    return result;
}

EPolynomialInsertSituation UPolynomial::WhereToAddWhenDuo(const FIndividual& inIndividual, int& outTargetIndex)
{
    outTargetIndex = 0;
    switch (inIndividual.ExponentCompareWith(individualsArray[0]))
    {
    case Larger:
        return BeforeHead;
    case Equal:
        return ExponentFound;
    default:
        break;
    }
    for (auto it = individualsArray.CreateIterator(); (it + 1).IsValid(); ++it, ++outTargetIndex)
    {
        FIndividual leftIndi = *it;
        FIndividual rightIndi = *(it + 1);
        if (inIndividual.IsExponentSmallerThan(leftIndi) && inIndividual.IsExponentLargerThan(rightIndi))
        {
            outTargetIndex++;
            return InMiddle;
        }
        if (inIndividual.IsExponentEqualTo(leftIndi))
        {
            //return ExponentFound;
        }
        else if (inIndividual.IsExponentEqualTo(rightIndi))
        {
            outTargetIndex++;
        }
        else continue;
        return ExponentFound;
    }
    return AfterTair;
}

void UPolynomial::AddWhenSingle(const FIndividual& inIndividual)
{
    switch (inIndividual.ExponentCompareWith(individualsArray[0]))
    {
    case Larger:
        individualsArray.Insert(inIndividual, 0);
        break;
    case Equal:
        PlusTargetIndividual(0, inIndividual);
        break;
    case Smaller:
    default:
        individualsArray.Add(inIndividual);
        break;
    }
}

void UPolynomial::AddWhenDuo(const FIndividual& inIndividual)
{
    int targetIndex;
    switch (WhereToAddWhenDuo(inIndividual, targetIndex))
    {
    case BeforeHead:
        individualsArray.Insert(inIndividual, 0);
        break;
    case InMiddle:
        individualsArray.Insert(inIndividual, targetIndex);
        break;
    case AfterTair:
        individualsArray.Add(inIndividual);
        break;
    case ExponentFound:
        PlusTargetIndividual(targetIndex, inIndividual);
        break;
    default:
        break;
    }
}

bool UPolynomial::Useless(const FIndividual& inIndividual) const
{
    return (inIndividual.Coefficient == 0);
}

void UPolynomial::HandleUsage(const FIndividual& inIndividual)
{
    if (Useless(inIndividual))
    {
        bool removeSuccess;
        individualsArray.Remove(inIndividual, removeSuccess);
        if (!removeSuccess)
        {
            throw removeSuccess;
        }
    }
}

void UPolynomial::PlusTargetIndividual(int inTargetIndex, const FIndividual& inIndividual)
{
    FIndividual& targetIndividual = individualsArray[inTargetIndex];
    targetIndividual += inIndividual;
    HandleUsage(targetIndividual);
}

UPolynomial UPolynomial::operator -()
{
    FIndiArray newArray(individualsArray);
    newArray.ForEachIterator([](FIndiIterator it)->void
    {
        it->Coefficient *= -1;
    });
    return UPolynomial(newArray, false);
}

UPolynomial& UPolynomial::operator =(const UPolynomial& another)
{
    individualsArray = another.individualsArray;
    return Self;
}

UPolynomial& UPolynomial::Plus(const UPolynomial& another)
{
    FIndiIterator selfIt = individualsArray.CreateIterator();
    FIndiIterator anotherIt = const_cast<UPolynomial&>(another).individualsArray.CreateIterator();
    while (anotherIt.IsValid())
    {
        AddIndividual(*anotherIt);
        ++anotherIt;
    }
    return Self;
}

UPolynomial& UPolynomial::Minus(const UPolynomial& another)
{
    UPolynomial* anotherCopy = new UPolynomial(another);
    *anotherCopy = -*anotherCopy;
    return Plus(*anotherCopy);
}

UPolynomial& UPolynomial::Multiply(const FIndividual& inIndividual)
{
    if (Useless(inIndividual))
    {
        individualsArray.ClearArray();
    }
    else
    {
        individualsArray.ForEach([&](FIndividual& indi)->void
        {
            indi *= inIndividual;
        });
    }
    return Self;
}

UPolynomial& UPolynomial::Multiply(const UPolynomial& another)
{
    UPolynomial newPoly;
    const_cast<UPolynomial&>(another).individualsArray.ForEach([&](const FIndividual& indi)->void
    {
        if (!Useless(indi))
        {
            UPolynomial copy(Self);
            UPolynomial poly = copy.Multiply(indi);
            newPoly.Plus(poly);
        }
    });
    *this = newPoly;
    return Self;
}

UPolynomial UPolynomial::GetDerivated()
{
    UPolynomial copy(Self);
    return copy.Derivate();
}

UPolynomial& UPolynomial::Derivate()
{
    individualsArray.ForEach([&](FIndividual& indi)->void
    {
        indi.Derivate();
        HandleUsage(indi);
    });
    return Self;
}
