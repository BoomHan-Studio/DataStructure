#include "Demo.h"

ADemo::ADemo()
    :demoName("父类")
{
    
}

void ADemo::BeginPlay()
{
    UApplicationStatics::ClearScreen();
    Cout << "现在进入的是" << demoName << "。" << Endl;
}

void ADemo::DemonStration()
{
    int reply;
    do
    {
        BeginPlay();
        do
        {
            Cout << "演示结束，还需要再演示一遍吗(1/0)?";
            UDataHandleStatics::InputNumber(reply);
        }while ((reply != 1) && (reply != 0));
    }while (reply == 1);
    Cout << "演示结束。" << Endl;
}

ADemo::~ADemo()
{
    
}
