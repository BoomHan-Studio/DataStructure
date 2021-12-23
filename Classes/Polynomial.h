#pragma once
#include "Structs/Array.h"
#include "Structs/Individual.h"
#include "CoreMinimal.h"

/**
 *@brief 类：一元多项式
 */
class UPolynomial
{
private:

    typedef TArray<FIndividual> FIndiArray;
    typedef TArrayIterator<FIndividual> FIndiIterator;

	friend class ADemoOfPolynomial;

    /**
     *单项式数组
     */
    FIndiArray individualsArray;
public:

    /**
     *@brief 构造函数，通过单项式链表构造一个多项式。
     *@param inArray 输入的链表对象引用
     *@param shouldSort 是否应该重新排序，默认下是的
     */
    UPolynomial(const FIndiArray& inArray, bool shouldSort = true);

    /**
     *@brief 默认构造函数。
     */
    UPolynomial();

    /**
     *@brief 拷贝构造函数。
     */
    UPolynomial(const UPolynomial& another);

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

    /**
     *@brief 添加一个单项式。
     *@param coef 添加的单项式系数
     *@param expo 添加的单项式指数
     *@note 当添加完成后，需要对该单项式进行插入。
     */
    void AddIndividual(double coef = 0, int expo = 0);

    /**
     *@brief 按遍历顺序转化为字符串。
     *@param inMethod 打印的方式，由低到高或由高到低
     *@param inDisplayChar 打印的多项式的字母表示，默认为x
     *@return 转化后的字符串
     */
    String ToString(ETraversalMethod inMethod = Sequential, char inDisplayChar = 'x');

    /**
     *
     */
    UPolynomial& Plus(const UPolynomial& another);

    /**
     *
     */
    UPolynomial& Minus(const UPolynomial& another);

    /**
     *
     */
    UPolynomial& Multiply(const UPolynomial& another);

    /**
     *
     */
    UPolynomial& Multiply(const FIndividual& inIndividual);

    /**
     *
     */
    UPolynomial GetDerivated();

    /**
     *
     */
    UPolynomial& Derivate();

    /**
     *
     */
    UPolynomial operator -();

    /**
     *
     */
    UPolynomial& operator =(const UPolynomial& another);
   
#pragma region PrivateFunctions

private:

    /**
     *@brief 重新排序多项式，顺序是从高到低。
     */
    void Sort();

    /**
     *@brief 当多项式不止一项时应该在哪里添加单项式。
     *@param inIndividual 添加的单项式对象引用
     *@param outTargetIndex 输出的对应索引值
     *@return 该单项式的插入方式(枚举值)
     */
    EPolynomialInsertSituation WhereToAddWhenDuo(const FIndividual& inIndividual, int& outTargetIndex);

    /**
     *@brief 当多项式只有一项时添加单项式。
     *@param inIndividual 添加的单项式对象引用
     */
    void AddWhenSingle(const FIndividual& inIndividual);

    /**
     *@brief 当多项式不止一项时添加单项式。
     *@param inIndividual 添加的单项式对象引用
     */
    void AddWhenDuo(const FIndividual& inIndividual);

    /**
     *@brief 是否为无用项。
     *@param inIndividual 被检查的单项式对象引用
     *@return 该单项式的系数为0则返回真，否则返回假。
     */
    bool Useless(const FIndividual& inIndividual) const;

    /**
     *
     */
    void HandleUsage(const FIndividual& inIndividual);

    /**
     *@brief 两单项式相加，其中一个是自身的某一项，另一个是外部的单项式。
     *@param inTargetIndex 指定自身项索引
     *@param inIndividual 添加的单项式对象引用
     */
    void PlusTargetIndividual(int inTargetIndex, const FIndividual& inIndividual);

#pragma endregion PrivateFunctions
};