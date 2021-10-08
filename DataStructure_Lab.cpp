#include "Classes/Polynomial.h"
#include "CoreMinimal.h"

#ifdef COREMINIMAL
using namespace std;
#endif

/*class TestClass
{
public:
    void TestFunction()
    {
        cout << "有一个人前来买瓜。" << endl;
    }
};

//模板指针结构体，想要拥有与原始指针相同的用法
template<typename T>
struct TObjectPtr
{
    S_PROTECTED(T* rawPtr);//原始指针

    TObjectPtr(T* inRaw)
        :rawPtr(inRaw)
    {
        
    }

    T& operator *()
    {
        return (*rawPtr);
    }

    T* operator =(T* inPtr)
    {
        rawPtr = inPtr;
        return rawPtr;
    }

    T* operator ->()
    {
        return rawPtr;
    }
};*/

int main()
{
    TArray<FIndividual> individuals;
    individuals.Add(FIndividual(3,6), FIndividual(7.014, 7), FIndividual(-4, 12));
    //individuals.Add(FIndividual(2,3));
    //individuals.Add(FIndividual(2.14, 2));
    FIndividual indi(2.732, 8);
    individuals.Add(indi);
    //individuals.Insert(indi, individuals.CreateIterator());
    UPolynomial* polynomial = new UPolynomial(individuals);
    polynomial->AddIndividual(FIndividual(1, 9));
    polynomial->PrintF(HighToLow);
    //cout << individuals.GetSize() << endl;

    /*TArray<int> intArray;
    intArray.Add(1, -3, 9, 7, 100.1);
    bool addUniquesSuccess;
    intArray.AddUnique(addUniquesSuccess, 1, 2, -4, 5.15645);
    cout << UDataHandleStatics::ToString(addUniquesSuccess) << endl;
    intArray.SortArray(Inverted);
    intArray.PrintF();*/
    
}