#pragma once
#include "BinaryTree.h"
#include "FunctionLibrarys/DataHandleStatics.h"

template <typename T>
TTreeNode<T>::TTreeNode(uint32 inNodeName, const T& inData)
	:Data(inData),
	NodeName(inNodeName),
	Parent(nullptr),
	LeftChild(nullptr),
	RightChild(nullptr)
{
	
}

template <typename T>
TTreeNode<T>::TTreeNode(const TTreeNode& another)
	:Data(another.Data),
	NodeName(another.NodeName),
	Parent(another.Parent),
	LeftChild(another.LeftChild),
	RightChild(another.RightChild)
{
	
}

template <typename T>
uint16 TTreeNode<T>::Degree() const
{
	return (LeftChild != nullptr) + (RightChild != nullptr);
}

template <typename T>
bool TTreeNode<T>::IsLeafNode() const
{
	return (Degree() == 0);
}

template <typename T>
void TTreeNode<T>::AddNode(ETreeNodeChildDirection inChildNodeName, TTreeNode* inNode)
{
	TTreeNode*& targetChild = GetChildByEnum(inChildNodeName);
	targetChild = inNode;
	inNode->Parent = targetChild;
}

template <typename T>
TTreeNode<T>*& TTreeNode<T>::GetChildByEnum(ETreeNodeChildDirection inChildNodeName)
{
	return (inChildNodeName == Left) ? LeftChild : RightChild;
	//return ((inChildNodeName == Left) ? static_cast<const TTreeNode&>(*this).LeftChild : static_cast<const TTreeNode&>(*this).RightChild);
}

template <typename T>
TTreeNode<T>::~TTreeNode()
{
	Data = T(0);
	UDataHandleStatics::Delete(LeftChild);
	UDataHandleStatics::Delete(RightChild);
}
