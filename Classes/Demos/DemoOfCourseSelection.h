#pragma once
#include "Demo.h"

class ADemoOfCourseSelection : public ADemo
{
public:
	
	//构造函数
	ADemoOfCourseSelection();

	//程序开始运行时调用它，可以把它当作main来写
	virtual void BeginPlay() override;

	//析构函数，释放指针等
	virtual ~ADemoOfCourseSelection() override;
	
private:

	//在这里写其他变量
};
