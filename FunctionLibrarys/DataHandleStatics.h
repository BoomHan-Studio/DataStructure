#pragma once
#include "CoreMinimal.h"

class UDataHandleStatics
{
private:
    /**
     *@brief 此类禁止构造。
     */
    UDataHandleStatics()
    {
        
    }
public:

    /**
     *@brief 判断两个单精度浮点数是否相等。
     *@param inA 浮点数A对象引用
     *@param inB 浮点数B对象引用
     *@return 若A B差值绝对值小于1e-4则返回真，否则返回假。
     */
    static bool IsNearlyEqual(const float& inA, const float& inB);

    /**
     *@brief 判断两个双精度浮点数是否相等。
     *@param inA 浮点数A对象引用
     *@param inB 浮点数B对象引用
     *@return 若A B差值绝对值小于1e-8则返回真，否则返回假
     */
    static bool IsNearlyEqual(const double& inA, const double& inB);

    /**
     *@brief 输入一个布尔值，转换为字符串。
     *@param inBool 输入的布尔值对象引用
     *@return Yes或No
     */
    static std::string ToStringFromBool(const bool& inBool);

    template<typename T>
    static std::string ToStringFromNumber(const T& inNumber)
    {
        std::stringstream stream;
        std::string result;
        stream << inNumber;
        stream >> result;
        return result;
    }

    /**
     *@brief 求绝对值，没什么好说的。
     */
    template<typename T>
    static T Absolution(const T& inNum)
    {
        return (inNum * (inNum >= 0 ? 1 : -1));
    }

    /**
     *@brief 交换两值A B。
     *@param inA 任意类型数据A首地址
     *@param inB 任意类型数据B首地址
     *@note 此重载版本会调用A B所属类型的默认拷贝构造函数，若有特殊需要请调用下一个重载版本。
     */
    template<typename T>
    static void Swap(T* inA, T* inB)
    {
        if ((!inA) || (!inB))
        {
            return;
        }
        T temp = *inA;
        *inA = *inB;
        *inB = temp;
    }

    /**
     *@brief 交换两值A B。
     *@param inA 任意类型数据A首地址
     *@param inB 任意类型数据B首地址
     *@param inCopyMethod 将右值赋给左值的函数(方法)
     *@note 此重载版本可自由定义拷贝值的方法。
     */
    template<typename T, typename FunctionType>
    static void Swap(T* inA, T* inB, FunctionType inCopyMethod)
    {
        if ((!inA) || (!inB))
        {
            return;
        }
        T temp;
        inCopyMethod(&temp, inA);
        inCopyMethod(inA, inB);
        inCopyMethod(inB, &temp);
    }
};
