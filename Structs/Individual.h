#pragma once
#include "CoreMinimal.h"

/**
 *结构体：单项式
 */
struct FIndividual
{
    /**
     *系数
     */
    double Coefficient;

    /**
     *指数
     */
    int Exponent;

    /**
     *@brief 构造函数。
     *@param coef 系数
     *@param expo 指数
     */
    FIndividual(const double coef = 1, const int expo = 0);

    /**
     *@brief 拷贝构造函数。
     *@param another 另一个单项式对象引用
     */
    FIndividual(const FIndividual& another);

    /**
     *@brief 析构函数。
     */
    ~FIndividual();

    /**
     *@brief 转化为字符串。
     *@param isSignedIfPositive 如果系数为正数是否带有符号
     *@param inDisplayChar 展示的字母，默认为x
     *@return 一个成型的字符串
     */
    String ToString(bool isSignedIfPositive = true, char inDisplayChar = 'x') const;

    /**
     *@brief 指数是否相等。
     *@param another 另一个单项式对象引用
     *@return 两者的指数是否相等
     */
    bool IsExponentEqualTo(const FIndividual& another) const;

    /**
     *@brief 指数是否比另一个大。
     *@param another 另一个单项式对象引用
     *@return 前者的指数是否更大
     */
    bool IsExponentLargerThan(const FIndividual& another) const;

    /**
     *@brief 指数是否比另一个小。
     *@param another 另一个单项式对象引用
     *@return 前者的指数是否更小
     */
    bool IsExponentSmallerThan(const FIndividual& another) const;

    /**
     *@brief 指数对比，返回一个枚举值。
     *@param another 另一个单项式对象引用
     *@return 两者的指数大小情况
     */
    EExponentsCompare ExponentCompareWith(const FIndividual& another) const;

    /**
     *@brief 求导运算。
     *@note 将改变自身的值。
     */
    void Derivate();

    /**
     *
     */
    FIndividual& operator =(const FIndividual& another);

    /**
     *@brief 两单项式是否相等。
     *@param another 另一个单项式对象引用
     *@return 二者的系数、指数是否都相等
     */
    bool operator ==(const FIndividual& another) const;

    /**
     *@brief 指数是否比另一个大。
     *@param another 另一个单项式对象引用
     *@return 前者的指数是否更大
     */
    bool operator >(const FIndividual& another) const;

    /**
     *@brief 指数是否比另一个小。
     *@param another 另一个单项式对象引用
     *@return 前者的指数是否更小
     */
    bool operator <(const FIndividual& another) const;

    /**
     *@brief 指数是否不比另一个小。
     *@param another 另一个单项式对象引用
     *@return 前者的指数是否不是更小
     */
    bool operator >=(const FIndividual& another) const;

    /**
     *@brief 指数是否不比另一个大。
     *@param another 另一个单项式对象引用
     *@return 前者的指数是否不是更大
     */
    bool operator <=(const FIndividual& another) const;

    /**
     *@brief 运算符+=，对另一个单项式求加法。
     *@param another 另一个单项式对象引用
     *@note 两单项式指数必须相等，否则无法相加!
     */
    FIndividual& operator +=(const FIndividual& another);

    /**
     *@brief 运算符-=，对另一个单项式求减法。
     *@param another 另一个单项式对象引用
     *@note 两单项式指数必须相等，否则无法相减!
     */
    FIndividual& operator -=(const FIndividual& another);

    /**
     *
     */
    FIndividual& operator *=(const FIndividual& another);

    /**
     *@brief 运算符+，对另一个单项式求加法。
     *@param another 另一个单项式对象引用
     *@return 两者相加后得出的新单项式
     *@note 两单项式指数必须相等，否则无法相加!
     */
    const FIndividual operator +(const FIndividual& another);

    /**
     *@brief 运算符-，对另一个单项式求减法。
     *@param another 另一个单项式对象引用
     *@return 两者相减后得出的新单项式
     *@note 两单项式指数必须相等，否则无法相减!
     */
    const FIndividual operator -(const FIndividual& another);

    /**
     *
     */
    const FIndividual operator *(const FIndividual& another);
};
