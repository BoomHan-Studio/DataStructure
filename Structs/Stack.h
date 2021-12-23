#pragma once
#include "CoreMinimal.h"
#define STACK_IDEAL_SIZE 50

template<typename T>
struct TStack
{
    const uint32 StackSize/*堆栈容量*/;
    S_PRIVATE(T* stackArray)/*堆栈数组*/;
	S_PRIVATE(uint32 currentElements)/*当前元素个数*/;

	//删除拷贝构造函数
	TStack(const TStack&) = delete;
	//删除赋值运算符
	const TStack& operator =(const TStack&) = delete;
	/**
	 *@brief 构造函数，构造一个最大容量为inMaxSize的栈。
	 *@param inMaxSize 想要的最大容量
	 *@note 通常情况下可以直接构造一个50容量的栈。但是当一些情况下需求量较大时，可以申请一个更大的容量。
	 */
    explicit TStack(uint32 inMaxSize = STACK_IDEAL_SIZE);

	~TStack();

	/**
	 *@brief 强制类型转换为bool，值为是否为空栈。
	 *@return (!Empty()) 
	 */
	operator bool() const noexcept;

	/**
	 *@brief 压栈。将一个元素压入栈顶。
	 *@param inValue 目标压栈元素
	 *@note 如果栈已满，将会触发异常!
	 */
	void PushStack(const T& inValue);

	/**
	 *@brief 是否为空栈。
	 *@return 栈的元素个数是否为0
	 */
	bool Empty() const noexcept;

	/**
	 *@brief 获取一个栈顶的对象引用。
	 *@return 栈顶元素(按引用)
	 *@note 如果栈为空，将会触发异常!
	 */
	T& Top();

	/**
	 *@brief 抛出栈顶元素。
	 *@return 栈顶元素(按值)
	 *@note 如果栈为空，，将会触发异常!
	 */
	T Pop();

private:

	/**
	 *@brief 检查栈是否已满。如果是，则会抛出异常。
	 */
	void CheckIfFull() const;

	/**
	 *@brief 检查栈是否为空。如果是，则会抛出异常。
	 */
	void CheckIfEmpty()	const;
};

#include "Stack.inl"