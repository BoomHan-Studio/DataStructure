#pragma once
#include "Core.h"
#include "Classes/Polynomial.h"
#include "Classes/Demos/DemoOfBinaryTree.h"
#include "Classes/Demos/DemoOfPolynomial.h"
#include "Classes/Demos/DemoOfBrackets.h"
#include "Classes/Demos/DemoOfCourseSelection.h"

class ADemoCreator
{
    using CreationFunction = ADemo* (ADemoCreator::*)();
    
    TMap<int, CreationFunction> creationMap;

    TArray<int> demosArray;
public:
    
    ADemoCreator()
        :creationMap{{1, &ADemoCreator::CreateDemoOfPolynomial},
        			 {2, &ADemoCreator::CreateDemoOfBrackets},
					 {3, &ADemoCreator::CreateDemoOfBinaryTree},
					 {4, &ADemoCreator::CreateDemoOfCourseSelection}},
		demosArray(TArray<int>()),
		demo(nullptr)
    {
        
    }

	~ADemoCreator()
    {
	    delete demo;
    }

    void ShowDemosList()
    {
        /*cout << "1.多项式运算" << endl;
        cout << "2.括号匹配检验" << endl;
    	cout << "3.二叉树的相关操作演示" << endl;
    	cout << "4.学生选课系统" << endl;

        cout << "请选择:";*/
    }
    
    ADemo* CreateDemo(int inCommand)
    {
        if (demosArray.Contains(inCommand) || creationMap.find(inCommand) == creationMap.end())
        {
            return nullptr;
        }
        demosArray.Add(inCommand);
        auto executedFunction = creationMap[inCommand];
        return (this->*executedFunction)();
    }

private:

	ADemo* demo;

    FORCEINLINE ADemo* CreateDemoOfPolynomial()
    {
		demo = new ADemoOfPolynomial();
        return demo;
    }

    FORCEINLINE ADemo* CreateDemoOfBrackets()
    {
    	demo = new ADemoOfBrackets();
        return demo;
    }

	FORCEINLINE ADemo* CreateDemoOfBinaryTree()
    {
    	demo = new ADemoOfBinaryTree();
    	return demo;
    }

	FORCEINLINE ADemo* CreateDemoOfCourseSelection()
    {
	    demo = new ADemoOfCourseSelection();
    	return demo;
    }
};

void OpenDemo()
{
    ADemoCreator* creator = new ADemoCreator();
    creator->ShowDemosList();
    /*int reply;
    UDataHandleStatics::InputNumber(reply);*/
    ADemo* demo = creator->CreateDemo(4);
    if (demo)
    {
        demo->DemonStration();
    }
}