#pragma once
#include "Core.h"

/**
 *@brief 演示程序 父类。
 */
class ADemo
{
protected:
    String demoName;
public:
	
    /**
     *@brief 默认构造函数。
     */
    ADemo();

protected:
    /**
     *@brief 演示开始时调用。
     */
    virtual void BeginPlay();

public:

    /**
     *@brief 会在被构造后立刻调用。
     */
    void DemonStration();
    
    /**
     *@brief 析构函数。
     */
    virtual ~ADemo();
};
