#pragma once
#include "Array.h"

template<typename T>
struct TStack : TArray<T>
{
    typedef TArray<T> Parent;
    typedef TLinkNode<T> FNode;

    using Parent::Add;
    using Parent::size;
    using Parent::RemoveByIndex;
    using Parent::Head;
    using Parent::Tair;
    using Parent::ForEachNode;
    using Parent::Free;

    uint sizeMax;
    
public:

    
    TStack(uint inSizeMax)
        :Parent(),
        sizeMax(inSizeMax)
    {
        
    }

    void PushStack(const T& inValue)
    {
        if (size <= sizeMax)
        {
            Add(inValue);
        }
    }

    void PushStack(const T& inValue, bool& outStatus)
    {
        outStatus = false;
        if (size <= sizeMax)
        {
            Add(inValue, outStatus);
        }
    }

    void Pop()
    {
        RemoveByIndex(size - 1);
    }

    T& Top()
    {
        return Tair->Element;
    }

    bool Empty() const
    {
        return (size == 0);
    }

    ~TStack()
    {
        ForEachNode([&](FNode* node)->void
        {
            Free(node);
        });
    }

    template<typename T1>
    friend void Display(const TStack<T1>& inStack);
};

template<typename T1>
void Display(const TStack<T1>& inStack)
{
    const_cast<TStack<T1>&>(inStack).PrintF();
}