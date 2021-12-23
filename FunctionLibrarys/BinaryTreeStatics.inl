#pragma once
#include "BinaryTreeStatics.h"

#define END "-N-"

static bool tempBoolean = false;

template<typename T>
FORCEINLINE void PrintTip(const TTreeNode<T>* inNode, ETreeNodeChildDirection inDirection)
{
	cout << "请输入" << inNode->NodeName << "号结点的" << (inDirection == Left ? "左" : "右") << "子结点:";
}

template<typename T>
FORCEINLINE String GetName()
{
	return String(typeid(T).name());
}

template<typename T>
bool InputValueInTree(T& outValue)
{
	String input;
	std::getline(cin, input);
	if (input == END)
	{
		return false;
	}
	outValue = UDataHandleStatics::ToNumberFromString<T>(input);
	return true;
}

template <typename T>
TBinaryTree<T>* UBinaryTreeStatics::CreateBinaryTree()
{
	using FBinaryTree = TBinaryTree<T>;
	using FTreeNode = typename FBinaryTree::FTreeNode;
	FBinaryTree* result = new FBinaryTree();
	cout << "现在开始创建" << typeid(T).name() <<"二叉树。输入" END "代表此结点为空。请输入根结点(1号结点):";
	if (!InputValueInTree(result->Root->Data))
	{
		delete result;
		return nullptr;
	}
	TStack<FTreeNode*> nodeStack;
	nodeStack.PushStack(result->Root);
	while (nodeStack)
	{
		FTreeNode* node = nodeStack.Top();
		T leftValue;
		T rightValue;
		if (!node->LeftChild)
		{
			PrintTip(node, Left);
			if (InputValueInTree(leftValue))
			{
				result->AddNode(node, leftValue, Left, tempBoolean);
				nodeStack.PushStack(node->LeftChild);
				continue;
			}
		}
		node = nodeStack.Pop();
		PrintTip(node, Right);
		if (InputValueInTree(rightValue))
		{
			result->AddNode(node, rightValue, Right, tempBoolean);
			nodeStack.PushStack(node->RightChild);
		}
	}
	return result;
}

template <typename T>
void UBinaryTreeStatics::TraverseTree(TBinaryTree<T>* inTree)
{
	cout << "该" << GetName<T>() << "型二叉树遍历结果如下。\n先序遍历:";
	inTree->ForEach([](T inValue)->void
	{
		cout << inValue << '\t';
	}, Sequence);
	cout << endl << "中序遍历:";
	inTree->ForEach([](T inValue)->void
	{
		cout << inValue << '\t';
	}, Secondary);
	cout << endl << "后序遍历:";
	inTree->ForEach([](T inValue)->void
	{
		cout << inValue << '\t';
	}, Rear);
	cout << endl << "层级遍历:";
	inTree->ForEach([](T inValue)->void
	{
		cout << inValue << '\t';
	}, Level);
	cout << endl;
}

template <typename T>
void UBinaryTreeStatics::PrintAllLeaves(TBinaryTree<T>* inTree)
{
	using FTreeNode = typename TBinaryTree<T>::FTreeNode;
	TQueue<FTreeNode*> nodeQueue;
	inTree->ForEachNode([&](FTreeNode* inNode)->void
	{
		if (inNode->IsLeafNode())
		{
			nodeQueue.Enqueue(inNode);
		}
	}, Rear);
	cout << "该" << GetName<T>() << "型二叉树叶子结点个数:" << nodeQueue.GetCurrentSize() << ",分别为:" << endl;
	while (nodeQueue)
	{
		FTreeNode* node = nodeQueue.Dequeue();
		cout << node->NodeName << "号结点:" << node->Data << endl;
	}
}

template<typename T>
void UBinaryTreeStatics::PrintTree(TTreeNode<T>* inNode, uint16 inHeight)
{
	uint16 i = 0;
	if (!inNode) return;
	PrintTree(inNode->RightChild, inHeight + 1);
	while (i < inHeight)
	{
		cout << '\t';
		i++;
	}
	cout << inNode->Data << "(" << inNode->NodeName << ")" << endl;
	PrintTree(inNode->LeftChild, inHeight + 1);
}

template <typename T>
void UBinaryTreeStatics::PrintTree(TBinaryTree<T>* inTree)
{
	if (!inTree) return;
	cout << "该" << GetName<T>() << "型二叉树形状:\n";
	PrintTree(inTree->Root, 0);
	cout << "二叉树高度:" << inTree->Height() << endl;
}
