#pragma once
#include "LinkNode.h"
#include "CoreMinimal.h"
#include "FunctionLibrarys/DataHandleStatics.h"
#include "FunctionLibrarys/DebugStatics.h"

/**
 *@brief 模板结构体：数组(链表)
 */
template<typename T>
struct TArray
{
    using FNode = TLinkNode<T>;
    using Compare = FNode* (TArray::*)(FNode*) const;
    
    template<typename T1>
    friend struct TArrayIterator;

    using FIterator = TArrayIterator<T>;
    
    /**
     *头结点(保护成员!)
     */
    S_PROTECTED(FNode* Head);

    /**
     *尾结点(保护成员!)
     */
    S_PROTECTED(FNode* Tair);

    /**
     *链表
     */
    FNode* LinkNode;

    /**
     *链表元素个数(保护成员!)
     */
    S_PROTECTED(uint size);

    /**
     *@brief 构造函数，生成若干个相同值的元素
     *@param inSize 构造的元素个数
     *@param inValue 每个元素的值右值引用
     */
    TArray(T&& inValue, int inSize = 1)
    :LinkNode(new FNode(inValue)),
	Head(LinkNode),
    Tair(Head),
    size(1)
    {
        for (; inSize > 1; inSize--)
        {
            Add(inValue);
        }
        Tair->Next = nullptr;
    }

    /**
     *@brief 默认构造函数，构造空数组。
     */
    TArray()
    :Head(nullptr),
    Tair(nullptr),
	LinkNode(nullptr),
    size(0)
    {
        
    }

    /**
     *@brief 拷贝构造函数。
     */
    TArray(const TArray& another)
        :Head(nullptr),
        Tair(nullptr),
        size(0)
    {
        for (FNode* node = another.Head; node; node = node->Next)
        {
            Add(node->Element);
        }
    }

    /**
     *@brief 输出函数，将每个元素打印在屏幕上
     *@param inMethod 打印的方式：顺序打印Sequential，倒叙打印Inverted
     *@note 要输出的模板类型T如果是struct或class，必须重载运算符<<，否则无法调用!!!!!!
     */
    void PrintF(ETraversalMethod inMethod = Sequential)
    {
        ForEach([](T ele)->void
        {
            std::cout << ele << std::endl;
        }, inMethod);
    }

    /**
     *@brief 在数组的末尾添加元素。
     *@param inValue 添加的元素值对象引用
     */
    void Add(const T& inValue)
    {
        /*if (!size)
        {
            LinkNode->Element = inValue;
            Head = &LinkNode;
            Tair = Head;
        }
        else
        {
            FNode* newNode = new FNode(inValue, Tair);
            Tair->Next = newNode;
            Tair = newNode;
        }
        size++;*/
    	if (!size)
    	{
    		LinkNode = new FNode(inValue);
    		Head = LinkNode;
    		Tair = Head;
    	}
    	else
    	{
    		FNode* newNode = new FNode(inValue, Tair);
    		Tair->Next = newNode;
    		Tair = newNode;
    	}
    	size++;
    }

    /**
     *@brief 在数组末尾添加多个元素。
     *@param inValue 添加的首个元素值对象引用
     *@param inValues 更多元素值对象引用
     *@note 无论后续添加什么类型的元素，都会被转化为该数组的模板类型。
     */
    template<typename ... Ts>
    void Add(const T& inValue, const Ts& ... inValues)
    {
        Add(inValue);
        Add(T(inValues) ...);
    }

    /**
     *@brief 在数组的末尾添加元素
     *@param inValue 添加的元素值对象引用
     *@param outStatus 是否添加成功
     *@note 这个重载版本还能输出添加成功与否，如不需要获取这个值，调用另一个重载版本。
     */
    void Add(const T& inValue, bool& outStatus)
    {
        outStatus = false;
        Add(inValue);
        outStatus = true;
    }

    /**
     *@brief 在数组的末尾添加值唯一的元素。
     *@param outStatus 是否添加成功
     *@param inValue 添加的元素值对象引用
     *@note 如果数组中已有此元素，则会添加失败。
     */
    void AddUnique(bool& outStatus, const T& inValue)
    {
        outStatus = !Contains(inValue);
        if (outStatus)
        {
            Add(inValue, outStatus);
        }
    }

    /**
     *@brief 在数组的末尾添加多个值唯一的元素。
     *@param outStatus 所有元素是否均添加成功
     *@param inValue 添加的首个元素值对象引用
     *@param inValues 添加的更多元素值对象引用
     *@note 如果数组中已有某个元素，则该元素不会被添加(其他元素不受影响)。
     */
    template<typename ... Ts>
    void AddUnique(bool& outStatus, const T& inValue, const Ts& ... inValues)
    {
        bool allSuccess;
        AddUnique(allSuccess, inValue);
        AddUnique(allSuccess, T(inValues) ...);
        outStatus = outStatus && allSuccess;
    }

    /**
     *@brief 在数组中插入元素。
     *@param inValue 插入的值对象引用
     *@param inIt 迭代器对象引用
     *@note 会在迭代器节点的前面插入一个新节点。
     */
    void Insert(const T& inValue, const FIterator& inIt)
    {
        if (!size)
        {
            Add(inValue);
        }
        else
        {
            if (!inIt.IsValid()) return;
            FNode* newNode = new FNode(inValue);
            FNode* itNode = const_cast<FIterator&>(inIt).ToRawNode();
            if (IsHead(itNode))
            {
                AddOnHead(newNode);
            }
            else
            {
                FNode* lastNode = itNode->Last;
                InsertNodes(lastNode, newNode, itNode);
            }
            size++;
        }
    }

    /**
     *@brief 在数组中插入元素。
     *@param inValue 插入的值对象引用
     *@param inIndex 目标索引值
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     *@note 会在目标索引的前面插入一个新节点。
     *@warnings 请不要在数组为空时插入元素，否则会引发异常!
     */
    void Insert(const T& inValue, int inIndex)
    {
        try
        {
            inIndex = ToRealIndex(inIndex);
        }
        catch (uint)
        {
            UDebugStatics::ExceptionWarning("Array.h", "Insert");
        }
        Insert(inValue, CreateIterator() + inIndex);
    }

    /**
     *@brief 在数组中插入值唯一的元素。
     *@param outStatus 是否添加成功
     *@param inValue 插入的值对象引用
     *@param inIt 迭代器对象引用
     *@note 会在迭代器节点的前面插入一个新节点。如果数组中已有此元素，则会插入失败。
     *@warnings 请不要在数组为空时插入元素，否则会引发异常!
     */
    void InsertUnique(bool& outStatus, const T& inValue, const FIterator& inIt)
    {
        outStatus = !Contains(inValue);
        if (outStatus)
        {
            Insert(inValue, inIt);
        }
    }

    /**
     *@brief 在数组中插入元素。
     *@param outStatus 是否添加成功
     *@param inValue 插入的值对象引用
     *@param inIndex 目标索引值
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     *@note 会在目标索引的前面插入一个新节点。如果数组中已有此元素，则会插入失败。
     *@warnings 请不要在数组为空时插入元素，否则会引发异常!
     */
    void InsertUnique(bool& outStatus, const T& inValue, uint inIndex)
    {
        try
        {
            inIndex = ToRealIndex(inIndex);
        }
        catch (uint)
        {
            UDebugStatics::ExceptionWarning("Array.h", "InsertUnique");
        }
        InsertUnique(outStatus, inValue, CreateIterator() + inIndex);
    }
    
    /**
     *@brief 是否包括某个值
     *@param inElement 输入的元素对象引用
     *@return 如果包括该值则返回真，否则返回假。
     */
    bool Contains(const T& inElement)
    {
        return (FindIndex(inElement) != NOT_FOUND);
    }

    /**
     *@brief 查找某个元素的索引
     *@param inElement 输入的元素对象引用
     *@return 若找到则返回其索引，否则返回-1。
     *@note 如果包括多个该值，输出第一个出现该值的索引。
     */
    int FindIndex(const T& inElement)
    {
        uint outIndex = 0;
        for (FIterator it = CreateIterator(); it.IsValid(); ++it, outIndex++)
        {
            if (inElement == *it)
            {
                return outIndex;
            }
        }
        return NOT_FOUND;
    }

    /**
     *@brief 按索引移除某个元素
     *@param inIndex 索引值
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    void RemoveByIndex(uint inIndex)
    {
        FNode& targetNode = At(inIndex);
        HandleInRemove(&targetNode);
        size--;
    }

    /**
     *@brief 按索引移除某个元素
     *@param inIndex 索引值
     *@param outStatus 移除是否成功
     *@note 此重载版本还能输出移除是否成功，如不需要这个值，请调用上一个版本。如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    void RemoveByIndex(uint inIndex, bool& outStatus)
    {
        outStatus = false;
        RemoveByIndex(inIndex);
        outStatus = true;
    }

    /**
     *@brief 按值移除某个元素
     *@param inElement 指定的元素对象引用
     *@param outStatus 移除是否成功
     *@note 此重载版本能按值移除元素。如果数组不包含此值，则不会发生任何事。
     */
    void Remove(const T& inElement, bool& outStatus)
    {
    	outStatus = false;
        const int targetIndex = FindIndex(inElement);
        if (targetIndex != -1)
        {
            RemoveByIndex(targetIndex, outStatus);
        }
    }

    /**
     *@brief 获取数组大小
     *@return 数组的元素个数
     */
    uint GetSize() const
    {
        return size;
    }

    /**
     *@brief 创建一个迭代器以供迭代。
     *@param inMethod 遍历方式
     *@return 如果是顺序遍历则返回一个从头节点开始的迭代器，否则返回从尾开始的迭代器
     */
    FIterator CreateIterator(ETraversalMethod inMethod = Sequential)
    {
        return FIterator(Self, inMethod);
    }

    /**
     *@brief 针对元素(值或引用)形成一个ForEach遍历。
     *@param inFunction 传入的函数指针
     *@param inMethod 遍历方式
     *@note 传入的函数指针必须是任意返回类型的、第一个参数类型为此数组模板类型T的函数。
     */
    template<typename FunctionType>
    void ForEach(FunctionType inFunction, ETraversalMethod inMethod = Sequential)
    {
        for (auto it = CreateIterator(inMethod); it.IsValid(); it.MoveIterator(inMethod))
        {
            inFunction(*it);
        }
    }

    /**
     *@brief 针对迭代器(值或引用)形成一个ForEach遍历。
     *@param inFunction 传入的函数指针
     *@param inMethod 遍历方式
     *@note 传入的函数指针必须是任意返回类型的、第一个参数类型为TArrayIterator<T>的函数。
     */
    template<typename FunctionType>
    void ForEachIterator(FunctionType inFunction, ETraversalMethod inMethod = Sequential)
    {
        for (auto it = CreateIterator(inMethod); it.IsValid(); it.MoveIterator(inMethod))
        {
            inFunction(it);
        }
    }

    /**
     *@brief 获取数组指定索引节点
     *@param inIndex 目标索引
     *@return 获取的节点对象引用
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    FNode& At(int inIndex)
    {
        try
        {
            inIndex = ToRealIndex(inIndex);
        }
        catch (uint)
        {
            UDebugStatics::ExceptionWarning("Array.h", "At");
        }
        ETraversalMethod method;
        int traversalTimes;
        GetTraverseDatas(inIndex, method, traversalTimes);
        FNode* beginNode = GetBeginNodeWithMethod(method);
        for (; traversalTimes; traversalTimes--)
        {
            beginNode = ToTargetPointer(beginNode, method);
        }
        return *beginNode;
    }

    /**
     *@brief 得到真实索引。
     *@param inIndex 输入的索引值
     *@return 对size求余后的索引
     */
    uint ToRealIndex(int inIndex) const
    {
        if ((!size) || (inIndex < 0))
        {
            throw size;
        }
        return (inIndex % size);
    }

    /**
     *@brief 得到数组指定索引的值
     *@param index 目标索引
     *@return 获取的模板类型对象引用
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    T& operator [](int index)
    {
        return At(index).Element;
    }

    /**
     *
     */
    TArray& operator =(const TArray& another)
    {
        ClearArray();
        for (FNode* node = another.Head; node; node = node->Next)
        {
            Add(node->Element);
        }
        return Self;
    }

    /**
     *@brief 为此数组由大到小排序。
     *@version 1.0
     *@param inMethod 排序方式，HighToLow是由高到低，LowToHigh是由低到高
     *@note 当前版本排序方法为：选择排序法，复杂度O(n^2)。
     */
    void SortArray(ESortMethod inMethod = HighToLow)
    {
        auto compare = (inMethod == LowToHigh ? [](const T& ta, const T& tb)->bool{return (ta <= tb);} : [](const T& ta, const T& tb)->bool{return (ta > tb);});
        if (size < 2) return;
        for (FNode* nodeI = Head; nodeI != Tair; nodeI = nodeI->Next)
        {
            FNode* targetNode = nodeI;
            for (FNode* nodeJ = nodeI->Next; nodeJ; nodeJ = nodeJ->Next)
            {
                if (compare(nodeJ->Element, targetNode->Element))
                {
                    targetNode = nodeJ;
                }
            }
            if (!nodeI->IsEqualTo(*targetNode, ValueRequired))
            {
                UDataHandleStatics::Swap(nodeI, targetNode, [](FNode* nodeA, FNode* nodeB)->void{nodeA->Element = nodeB->Element;});
            }
        }
    }

    /**
     *@brief 清空数组。
     */
    void ClearArray()
    {
        while (size)
        {
            RemoveByIndex(size - 1);
        }
    }

    /**
     *@brief 析构函数。
     */
    virtual ~TArray()
    {
    	ClearArray();
        /*while (Head->Next)
        {
            RemoveByIndex(1);
        }
        RemoveByIndex(0);*/
    }

#pragma region InnerFunctions

protected:

    /**
     *@brief 针对节点形成一个ForEach遍历。
     *@param inFunction 传入的函数指针
     *@param inMethod 遍历方式
     *@note 传入的函数指针必须是任意返回类型的、第一个参数类型为TLinkNode<T>的函数。
     */
    template<typename FunctionType>
    void ForEachNode(FunctionType inFunction, ETraversalMethod inMethod = Sequential)
    {
        for (auto it = CreateIterator(inMethod); it.IsValid(); it.MoveIterator(inMethod))
        {
            inFunction(it.ToRawNode());
        }
    }
    
    /**
     *@brief 根据不同方式得到下一个节点
     *@param inNode 输入的节点
     *@param inMethod 目标遍历方式
     *@return 如果是顺序遍历则返回Next节点，否则返回Last节点
     */
    FNode* ToTargetPointer(FNode* inNode, ETraversalMethod inMethod = Sequential)
    {
        Compare To;
        To = (inMethod == Sequential) ? &TArray::ToNext : &TArray::ToLast;
        return (this->*To)(inNode);
    }

    /**
     *@brief 获取Last节点
     *@param inNode 输入节点
     *@return inNode->Last
     */
    FNode* ToLast(FNode* inNode) const
    {
        return inNode->Last;
    }

    /**
     *@brief 获取Next节点
     *@param inNode 输入节点
     *@return inNode->Next
     */
    FNode* ToNext(FNode* inNode) const
    {
        return inNode->Next;
    }

    /**
     *@brief 根据遍历方式获得遍历开始的节点
     *@param inMethod 目标遍历方式
     *@return 若顺序遍历则返回头结点，否则返回尾结点
     */
    FNode* GetBeginNodeWithMethod(ETraversalMethod inMethod) const
    {
        return (inMethod == Sequential) ? Head : Tair;
    }

    /**
     *@brief 根据不同的索引，依照就近原则获得遍历数据
     *@param index 目标索引
     *@param outMethod 输出遍历方式
     *@param outTraversalTimes 输出遍历次数
     */
    void GetTraverseDatas(uint index, ETraversalMethod& outMethod, int& outTraversalTimes)
    {
        bool fromHead = (index < size / 2);
        outMethod = fromHead ? Sequential : Inverted;
        outTraversalTimes = fromHead ? index : size - index - 1;
    }
	
    /**
     *@brief 绑定前后两个节点，使二者指针域互相指向。
     *@param inFormerNode 前一个节点
     *@param inLatterNode 后一个节点
     *@note 顺序不能反！
     */
    void BindNodes(FNode* inFormerNode, FNode* inLatterNode)
    {
        inFormerNode->Next = inLatterNode;
        inLatterNode->Last = inFormerNode;
    }

    /**
     *@brief 将目标节点插入两个节点之间。
     *@param inFormerNode 前一个节点
     *@param inTargetNode 想要插入的节点
     *@param inLatterNode 后一个节点
     *@note 顺序不能反！
     */
    void InsertNodes(FNode* inFormerNode, FNode* inTargetNode, FNode* inLatterNode)
    {
        BindNodes(inFormerNode, inTargetNode);
        BindNodes(inTargetNode, inLatterNode);
    }

    /**
     *@brief 在头结点前插入节点，并使其成为新的头结点。
     *@param inNewNode 新的节点
     */
    void AddOnHead(FNode* inNewNode)
    {
        BindNodes(inNewNode, Head);
        Head = inNewNode;
    }

    /**
     *@brief 在移除节点时处理其相邻节点
     */
    void HandleInRemove(FNode* inTargetNode)
    {
        if (size == 1)
        {
            HandleSingle(inTargetNode);
        }
        else
        {
            HandleDuo(inTargetNode);
        }
        Free(inTargetNode);
    }

    /**
     *@brief 当只剩一个节点时的调用。
     */
    void HandleSingle(FNode* inTargetNode)
    {
        Head = nullptr;
        Tair = nullptr;
    }

    /**
     *用于删除某节点后节点剩余节点的拼接。
     *@brief 当还有超过一个节点时的调用。
     */
    void HandleDuo(FNode* inTargetNode)
    {
        FNode*& lastNode = inTargetNode->Last;
        FNode*& nextNode = inTargetNode->Next;
        if (IsHead(inTargetNode))
        {
            Head = nextNode;
            Head->Last = nullptr;
        }
        else if (IsTair(inTargetNode))
        {
            Tair = lastNode;
            Tair->Next = nullptr;
        }
        else
        {
            lastNode->Next = nextNode;
            nextNode->Last = lastNode;
        }
    }

    /**
     *@brief 两个节点是否为同一节点。
     *@param inNodeA 输入节点A
     *@param inNodeB 输入节点B
     *@return 两节点的数据域、指针域都相同则返回真，否则返回假。
     */
    bool IsEqualNodes(FNode* inNodeA, FNode* inNodeB) const
    {
        if ((!inNodeA) || (!inNodeB))
        {
            return false;
        }
        return (inNodeA == inNodeB);
    }

    /**
     *@brief 某节点是否为头结点。
     *@param inNode 输入节点
     *@return 若该节点是头结点则返回真，否则返回假。
     */
    bool IsHead(FNode* inNode) const
    {
        return IsEqualNodes(inNode, Head);
    }

    /**
     *@brief 某节点是否为头结点。
     *@param inNode 输入节点
     *@return 若该节点是头结点则返回真，否则返回假。
     */
    bool IsTair(FNode* inNode) const
    {
        return IsEqualNodes(inNode, Tair);
    }

    /**
     *@brief 释放节点指针
     *@param inNode 目标节点
     */
    void Free(FNode* inNode)
    {
        if (!inNode)
        {
            return;
        }
        /*inNode->Element = T(0);
        inNode->Last = nullptr;
        inNode->Next = nullptr;*/
    	delete inNode;
    }

#pragma endregion InnerFunctions
    
};

/**
 *@brief 模板结构体：链表迭代器
 */
template<typename T>
struct TArrayIterator
{
    typedef TLinkNode<T> FNode;

    /**
    *当前的指向节点
    */
    FNode* CurrentNode;

    /**
     *@brief 构造函数。
     *@param inArray 输入的链表
     *@param inMethod 迭代的方式
     *@note 迭代方式的不同会导致构造不同的迭代器。顺序遍历则迭代器在Head，否则在Tair。
     */
    TArrayIterator(const TArray<T>& inArray, ETraversalMethod inMethod = Sequential)
        :CurrentNode(inArray.GetBeginNodeWithMethod(inMethod))
    {
        
    }

    TArrayIterator(const TArrayIterator& another)
        :CurrentNode(another.CurrentNode)
    {
        
    }

    /**
     *@brief 转换为原始的节点。
     *@return 当前指向的节点
     */
    FNode*& ToRawNode()
    {
        return CurrentNode;
    }

    /**
     *@brief 迭代器是否有效。
     *@return 当前的节点是否为空指针
     */
    bool IsValid() const
    {
        return (CurrentNode != nullptr);
    }

    /**
     *@brief 根据遍历方式不同移动若干次。
     *@param inMethod 遍历方式
     *@param inMoveTimes 移动的次数
     *@note 如果是顺序遍历则向Next方向移动，否则向Last方向移动。
     */
    TArrayIterator& MoveIterator(ETraversalMethod inMethod, unsigned int inMoveTimes = 1)
    {
        while (inMoveTimes--)
        {
            (inMethod == Sequential) ? ++Self : --Self;
            if (!IsValid())
            {
                break;
            }
        }
        return Self;
    }

    

    bool operator >(const TArrayIterator& another)
    {
        TArrayIterator copy = Self;
        while (copy.IsValid())
        {
            --copy;
            if (copy.ToRawNode() == const_cast<TArrayIterator&>(another).ToRawNode())
            {
                return true;
            }
        }
        return false;
    }
    
    /**
     *@brief 迭代器向后移动一定单位，返回一个新的迭代器。
     *@param inNum 向后移动的单位数量
     */
    TArrayIterator operator +(unsigned int inNum)
    {
        TArrayIterator copy(Self);
        copy += inNum;
        return copy;
    }

    /**
     *@brief 迭代器向前移动一定单位，返回一个新的迭代器。
     *@param inNum 向前移动的单位数量
     */
    TArrayIterator operator -(unsigned int inNum)
    {
        TArrayIterator copy(Self);
        copy -= inNum;
        return copy;
    }

    /**
     *@brief 迭代器向后移动一定单位
     *@param inNum 向后移动的单位数量
     */
    TArrayIterator& operator += (unsigned int inNum)
    {
        while (inNum--)
        {
            ++Self;
        }
        return Self;
    }

    /**
     *@brief 迭代器向前移动一定单位
     *@param inNum 向前移动的单位数量
     */
    TArrayIterator& operator -=(unsigned int inNum)
    {
        while (inNum--)
        {
            --Self;
        }
        return Self;
    }

    /**
     *@brief 迭代器向后移动。
     *@return 指向的节点的Next节点
     */
    TArrayIterator& operator ++()
    {
        CurrentNode = CurrentNode->Next;
        return Self;
    }

    /**
     *@brief 迭代器向前移动。
     *@return 指向的节点的Last节点
     */
    TArrayIterator& operator --()
    {
        CurrentNode = CurrentNode->Last;
        return Self;
    }

    /**
     *@brief 解指针(实际上解的是节点的指针)。
     *@return 当前的元素对象引用
     */
    T& operator *() const
    {
        return CurrentNode->Element;
    }

    /**
     *@brief 解指针(实际上解的是节点的指针)。
     *@return 当前的元素对象引用
     */
    T& operator *()
    {
        return CurrentNode->Element;
    }

    /**
     *@brief 箭头操作符，有解指针操作。
     *@return 节点指向的数据域的地址
     */
    T* operator ->() const
    {
        return &(CurrentNode->Element);
    }

    /**
     *@brief 箭头操作符，有解指针操作。
     *@warning 有效性待定!
     */
    T* operator ->()
    {
        return &(CurrentNode->Element);
    }
};