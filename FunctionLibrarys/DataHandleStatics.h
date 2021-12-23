#pragma once
#include "Statics.h"

class UDataHandleStatics : UStatics
{
private:
    /**
     *@brief 此类禁止构造。
     */
    UDataHandleStatics() = delete;
public:

    /**
     *@brief 判断两个单精度浮点数是否相等。
     *@param inA 浮点数A对象引用
     *@param inB 浮点数B对象引用
     *@return 若A B差值绝对值小于1e-2则返回真，否则返回假。
     */
    static FORCEINLINE bool IsNearlyEqual(const float& inA, const float& inB);

    /**
     *@brief 判断两个双精度浮点数是否相等。
     *@param inA 浮点数A对象引用
     *@param inB 浮点数B对象引用
     *@return 若A B差值绝对值小于1e-4则返回真，否则返回假
     */
    static FORCEINLINE bool IsNearlyEqual(const double& inA, const double& inB);

    /**
     *@brief 输入一个布尔值，转换为字符串。
     *@param inBool 输入的布尔值
     *@param stringIfTrue 布尔值为真的字符串值，默认为Yes
     *@param stringIfFalse 布尔值为假的字符串值，默认为No
     *@return 依据布尔值的真假和自定义的输入返回的字符串
     */
    static FORCEINLINE String ToStringFromBool(bool inBool, String stringIfTrue = "Yes", String stringIfFalse = "No");

    /**
     *@brief 输入一个数字，转换为字符串。
     *@param inNumber 输入的数字对象引用
     *@return 转化后的字符串
     */
    template<typename T>
    static String ToStringFromNumber(const T& inNumber);

	template<typename T>
	static T ToNumberFromString(String inString);

    /**
     *@brief 求绝对值，没什么好说的。
     */
    template<typename T>
    static FORCEINLINE T Absolution(const T& inNumber);

	/**
	 *@brief 求两数的最大值的引用，没什么好说的。
	 */
	template<typename T>
	static FORCEINLINE T& Max(const T& inA, const T& inB);

	/**
	 *@brief 求两数的最大值的引用，没什么好说的。
	 */
	template<typename T>
	static FORCEINLINE T& Max(T&& inA, T&& inB);

    /**
     *@brief 求正切，没什么好说的。
     */
    static FORCEINLINE double Tan(const double& inNumber);

    /**
     *@brief 求反正切，没什么好说的。
     */
    static FORCEINLINE double ATan(const double& inNumber);

    /**
     *@brief 指定的某个值是否在某一区间内。
     *@param inNumber 指定的数
     *@param inMin 区间下界
     *@param inMax 区间上界
     *@param isLeftInclusive 左区间是否为闭区间
     *@param isRightInclusive 右区间是否为闭区间
     *@return 若inNumber在区间inMin~inMax内则返回真，否则返回假
     */
    template<typename T>
    static FORCEINLINE bool IsValueBetweenAnd(const T& inNumber, const T& inMin, const T& inMax, bool isLeftInclusive = false, bool isRightInclusive = false);

    /**
     *@brief 交换两值A B。
     *@param inA 任意类型数据A首地址
     *@param inB 任意类型数据B首地址
     *@note 此重载版本会调用A B所属类型的默认拷贝构造函数，若有特殊需要请调用下一个重载版本。
     */
    template<typename T>
    static FORCEINLINE void Swap(T* inA, T* inB);
    
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

	/**
	 *@brief 限制一个数在一区间内。
	 */
	template<typename T0, typename T = T0>
	static T Clamp(T0 inValue, T inMin, T inMax);

	/**
	 *@brief 删除一个指针。
	 *@param inPtr 待删除指针
	 *@warning 暂时没有稳定性，请慎用！
	 */
    template<typename T>
    static FORCEINLINE void Delete(const T* inPtr);

    /**
     *@brief 更安全、方便的scanf()/cin >>。
     *@param outInputValue 要从键盘输入赋值的对象
     *@note 这个函数会暂停程序调用cin。
     *@note 这个函数可以避免字符输入的弊端，例如：scanf("%d%c", &i, &c)时如果输入一个整数后回车，那么c会被直接赋值\\n。
     *@note 这个函数可以避免数据类型不匹配造成的毁灭性影响，例如：scnaf("%d", &i)时如果输入一个浮点数，可能导致后续输入全部异常。
     *@warning 不能用这个函数输入除数字外任何其他类型(包括char)，否则会导致崩溃！
     */
    template<typename T>
    static FORCEINLINE void InputNumber(T& outInputValue);

	static FORCEINLINE void InputChar(char& outInputChar);
};

#include "DataHandleStatics.inl"