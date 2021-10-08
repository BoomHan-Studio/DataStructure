#include "Classes/Polynomial.h"
#include <iostream>
#include "FunctionLibrarys/DataHandleStatics.h"
using namespace std;

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
    /*TArray<FIndividual> individuals;
    individuals.Add(FIndividual(1,3));
    individuals.Add(FIndividual(2.14, 2));
    FIndividual indi(2.732, 8);
    individuals.Add(indi);
    individuals.Insert(indi, individuals.CreateIterator());*/
    /*UPolynomial* polynomial = new UPolynomial(individuals);
    polynomial->PrintF();
    cout << individuals.GetSize() << endl;*/

    TArray<int> intArray;
    intArray.Add(1, 3, 6, 7, 100.1);
    bool addUniquesSuccess;
    intArray.AddUnique(addUniquesSuccess,  2, -4, 5.15645);
    //cout << addUniquesSuccess << endl;
    intArray.PrintF();
    cin.get();
    intArray.SortArray(Sequential);
    //intArray.PrintF();
    
}






/*TestClass* class1 = new TestClass();
class1->TestFunction();
    
TObjectPtr<TestClass> class2 = new TestClass();
class2->TestFunction();*/
