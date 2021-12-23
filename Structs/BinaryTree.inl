// ReSharper disable All
#pragma once
#include "BinaryTree.h"
#include "Stack.h"

template <typename T>
TBinaryTree<T>::TBinaryTree(FTreeNode* inRoot)
	:Root(new FTreeNode(1, Root->Data)),
	totalNodes(1)
{
	
}

template <typename T>
TBinaryTree<T>::TBinaryTree(const T& inData)
	:Root(new FTreeNode(1, inData)),
	totalNodes(1)
{
	
}

template <typename T>
uint16 TBinaryTree<T>::Height() const noexcept
{
	return Height(Root);
}

template <typename T>
uint16 TBinaryTree<T>::Height(FTreeNode* inNode) const noexcept
{
	if (!inNode) return 0;
	const uint16 leftHeight = Height(inNode->LeftChild);
	const uint16 rightHeight = Height(inNode->RightChild);
	return (UDataHandleStatics::Max(leftHeight, rightHeight) + 1);
}

template <typename T>
void TBinaryTree<T>::AddNode(uint32 inTargetNodeName, const T& inValue, ETreeNodeChildDirection inChildNodeName, bool& outAddSuccess)
{
	outAddSuccess = false;
	FTreeNode* targetNode = FindNode(inTargetNodeName);
	/*UDebugStatics::DebugLog(Log, "遍历次数:", traverseTime,
		" 目标节点是否找到:", UDataHandleStatics::ToStringFromBool(targetFound),
		" 目标节点是否为空指针:", UDataHandleStatics::ToStringFromBool(targetNode == nullptr),
		(targetNode != nullptr) ? " 目标节点名字:" + UDataHandleStatics::ToStringFromNumber(targetNode->NodeName) : "");*/
	AddNode(targetNode, inValue, inChildNodeName, outAddSuccess);
}

template <typename T>
void TBinaryTree<T>::AddNode(FTreeNode* inTargetNode, const T& inValue, ETreeNodeChildDirection inChildNodeName, bool& outAddSuccess)
{
	if (outAddSuccess = (inTargetNode && (inTargetNode->GetChildByEnum(inChildNodeName) == nullptr)))
	{
		totalNodes++;
		inTargetNode->AddNode(inChildNodeName, new FTreeNode(totalNodes, inValue));
	}
}

template <typename T>
void TBinaryTree<T>::DeleteNode(uint32 inDeleteNodeName, bool& outDeleteSuccess)
{
	FTreeNode* targetNode = FindNode(inDeleteNodeName);
	DeleteNode(targetNode, outDeleteSuccess);
}

template <typename T>
void TBinaryTree<T>::DeleteNode(const FTreeNode* inDeleteNode, bool& outDeleteSuccess)
{
	if (outDeleteSuccess = (inDeleteNode != nullptr))
	{
		ForEachNode([&](FTreeNode* inNode)->void
		{
			delete inNode;
		}, Rear);
	}
}

template <typename T>
typename TBinaryTree<T>::FTreeNode* TBinaryTree<T>::FindNode(uint32 inTargetNodeName)
{
	FTreeNode* targetNode = nullptr;
	bool targetFound = false;
	ForEachNodeWithBreak([&](FTreeNode* inNode)->void
	{
		targetNode = inNode;
	},[&](FTreeNode* inNode)->bool
	{
		return (targetFound = inNode->NodeName == inTargetNodeName);
	}, Rear);
	return (targetFound ? targetNode : nullptr);
}

template <typename T>
template <typename FunctionType>
void TBinaryTree<T>::ForEach(FunctionType inFunction, EBinaryTreeTraverseMethod inMethod)
{
	ForEachNode([&](FTreeNode* inNode)->void
	{
		inFunction(inNode->Data);
	}, inMethod);
}

template <typename T>
template <typename FunctionType, typename BreakType>
void TBinaryTree<T>::ForEachWithBreak(FunctionType inFunction, BreakType inBreakCondition, EBinaryTreeTraverseMethod inMethod)
{
	ForEachNodeWithBreak([&](FTreeNode* inNode)->void
	{
		inFunction(inNode->Data);
	}, inBreakCondition, inMethod);
}

template <typename T>
template <typename FunctionType>
void TBinaryTree<T>::ForEachNode(FunctionType inFunction, EBinaryTreeTraverseMethod inMehod, FTreeNode* inBeginNode)
{
	TMap<EBinaryTreeTraverseMethod, void (TBinaryTree::*)(FunctionType, FTreeNode*)> functionMap{
		{Sequence, &TBinaryTree::SequenceTraverse},
		{Secondary, &TBinaryTree::SecondaryTraverse},
		{Rear, &TBinaryTree::RearTraverse},
		{Level, &TBinaryTree::LevelTraverse}};
	(this->*functionMap[inMehod])(inFunction, inBeginNode ? inBeginNode : Root);
}

template <typename T>
template <typename FunctionType, typename BreakType>
void TBinaryTree<T>::ForEachNodeWithBreak(FunctionType inFunction, BreakType inBreakCondition, EBinaryTreeTraverseMethod inMehod, FTreeNode* inBeginNode)
{
	TMap<EBinaryTreeTraverseMethod, void (TBinaryTree::*)(FunctionType, BreakType, FTreeNode*)> functionMap{
		{Sequence, &TBinaryTree::SequenceTraverseWithBreak},
		{Secondary, &TBinaryTree::SecondaryTraverseWithBreak},
		{Rear, &TBinaryTree::RearTraverseWithBreak},
		{Level, &TBinaryTree::LevelTraverseWithBreak}};
	(this->*functionMap[inMehod])(inFunction, inBreakCondition, inBeginNode ? inBeginNode : Root);
}

template <typename T>
template <typename FunctionType, typename BreakType>
void TBinaryTree<T>::SequenceTraverseWithBreak(FunctionType inFunction, BreakType inBreakCondition, FTreeNode* inBeginNode)
{
	TStack<FTreeNode*> nodeStack;
	nodeStack.PushStack(inBeginNode);
	while (nodeStack)
	{
		FTreeNode* temp = nodeStack.Pop();
		inFunction(temp);
		if (inBreakCondition(temp))
		{
			return;
		}
		if (temp->RightChild) nodeStack.PushStack(temp->RightChild);
		if (temp->LeftChild) nodeStack.PushStack(temp->LeftChild);
	}
}

template <typename T>
template <typename FunctionType, typename BreakType>
void TBinaryTree<T>::SecondaryTraverseWithBreak(FunctionType inFunction, BreakType inBreakCondition, FTreeNode* inBeginNode)
{
	TStack<FTreeNode*> nodeStack;
	FTreeNode* temp = inBeginNode;
	do
	{
		while (temp)
		{
			nodeStack.PushStack(temp);
			temp = temp->LeftChild;
		}
		if (nodeStack)
		{
			temp = nodeStack.Pop();
			inFunction(temp);
			if (inBreakCondition(temp)) return;
			temp = temp->RightChild;
		}
	}while (temp || nodeStack);
}

template<typename T>
struct TStackNode
{
	using FTreeNode = TTreeNode<T>;

	FTreeNode* Node;
	ETreeNodeChildDirection Tag;

	TStackNode(FTreeNode* inNode = nullptr, ETreeNodeChildDirection inTag = Left)
		:Node(inNode),
		Tag(inTag)
	{
		
	}

	TStackNode(const TStackNode& another)
		:Node(another.Node),
		Tag(another.Tag)
	{
		
	}

	FORCEINLINE operator FTreeNode* ()
	{
		return Node;
	}

	const TStackNode& operator =(const TStackNode& another)
	{
		Node = another.Node;
		Tag = another.Tag;
		return Self;
	}
	
	const TStackNode& operator =(FTreeNode* inNode)
	{
		Node = inNode;
		return Self;
	}

	const TStackNode& operator =(ETreeNodeChildDirection inTag)
	{
		Tag = inTag;
		return Self;
	}
};

template <typename T>
template <typename FunctionType, typename BreakType>
void TBinaryTree<T>::RearTraverseWithBreak(FunctionType inFunction, BreakType inBreakCondition, FTreeNode* inBeginNode)
{
	using FStackNode = TStackNode<T>;
	TStack<FStackNode> stackNodeStack;
	FStackNode stackNode;
	FTreeNode* temp = inBeginNode;
	do
	{
		while (temp)
		{
			stackNode = FStackNode(temp, Left);
			stackNodeStack.PushStack(stackNode);
			temp = temp->LeftChild;
		}
		bool toContinue = true;
		while (toContinue && stackNodeStack)
		{
			stackNode = stackNodeStack.Pop();
			temp = stackNode;
			if (stackNode.Tag == Left)
			{
				stackNode = Right;
				stackNodeStack.PushStack(stackNode);
				toContinue = false;
				temp = temp->RightChild;
			}
			else
			{
				inFunction(temp);
				if (inBreakCondition(temp)) return;
			}
		}
	}while (stackNodeStack);
}

template <typename T>
template <typename FunctionType, typename BreakType>
void TBinaryTree<T>::LevelTraverseWithBreak(FunctionType inFunction, BreakType inBreakCondition, FTreeNode* inBeginNode)
{
	TQueue<FTreeNode*> nodeQueue;
	nodeQueue.ForceClear();
	nodeQueue.Enqueue(inBeginNode);
	while (nodeQueue)
	{
		FTreeNode* node = nodeQueue.Dequeue();
		inFunction(node);
		if (inBreakCondition(node)) return;
		if (node->LeftChild) nodeQueue.Enqueue(node->LeftChild);
		if (node->RightChild) nodeQueue.Enqueue(node->RightChild);
	}
}

template <typename T>
template <typename FunctionType>
void TBinaryTree<T>::SequenceTraverse(FunctionType inFunction, FTreeNode* inBeginNode)
{
	SequenceTraverseWithBreak(inFunction, [](FTreeNode* inNode)->bool{return false;}, inBeginNode);
}

template <typename T>
template <typename FunctionType>
void TBinaryTree<T>::SecondaryTraverse(FunctionType inFunction, FTreeNode* inBeginNode)
{
	SecondaryTraverseWithBreak(inFunction, [](FTreeNode* inNode)->bool{return false;}, inBeginNode);
}

template <typename T>
template <typename FunctionType>
void TBinaryTree<T>::RearTraverse(FunctionType inFunction, FTreeNode* inBeginNode)
{
	RearTraverseWithBreak(inFunction, [](FTreeNode* inNode)->bool{return false;}, inBeginNode);
}

template <typename T>
template <typename FunctionType>
void TBinaryTree<T>::LevelTraverse(FunctionType inFunction, FTreeNode* inBeginNode)
{
	LevelTraverseWithBreak(inFunction, [](FTreeNode* inNode)->bool{return false;}, inBeginNode);
}

template<typename T>
TBinaryTree<T>::~TBinaryTree()
{
	UDebugStatics::DebugLog(Log, "TBinaryTree<", typeid(T).name(), ">析构函数调用!");
	RearTraverse([&](FTreeNode* inNode)->void
	{
		delete inNode;
	});
}