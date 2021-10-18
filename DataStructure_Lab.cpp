#include "DataStructure_Lab.h"

void OpenDemo()
{
    ADemoCreator* creator = new ADemoCreator();
    creator->ShowDemosList();
    int reply;
    cin >> reply;
    ADemo* demo = creator->CreateDemo(reply);
    if (demo)
    {
        demo->DemonStration();
    }
}

int main()
{
    ADemoCreator* creator = new ADemoCreator();
    creator->ShowDemosList();
    int reply;
    cin >> reply;
    cin.get();
    ADemo* demo = creator->CreateDemo(reply);
    if (demo)
    {
        demo->DemonStration();
    }
    return 0;
}
