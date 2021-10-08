#pragma once
#include "Structs/Array.h"
#include "Structs/Individual.h"

#define C_PROTECTED(variable); protected:\
                                variable;\
                             private:\

#define C_PUBLIC(variable); public:\
                              variable;\
                          private:\

class UPolynomial
{
private:

    typedef TArray<FIndividual> FIndiArray;

    /**
     *单项式数组
     */
    FIndiArray individualsArray;

    /**
     *最高项数的指数
     */
    int maxExponent;


    
public:

    /**
     *@brief 构造函数，通过单项式链表构造一个多项式。
     *@param inArray 输入的链表对象引用
     *@param shouldSort 是否应该重新排序，默认下是的
     */
    UPolynomial(const FIndiArray& inArray, bool shouldSort = true);

    /**
     *@brief 按顺序遍历打印多项式。
     *@param inMethod 打印的方式，由低到高或由高到低
     *@param inDisplayChar 打印的多项式的字母表示，默认为x
     */
    void PrintF(ETraversalMethod inMethod = Sequential, char inDisplayChar = 'x');

    /**
     *@brief 添加一个单项式。
     *@param inIndividual 添加的单项式对象引用
     *@note 当添加完成后，需要对该单项式进行插入。
     */
    void AddIndividual(const FIndividual& inIndividual);

private:

    /**
     *@brief 重新排序多项式，顺序是从高到低。
     */
    void Sort();
};
