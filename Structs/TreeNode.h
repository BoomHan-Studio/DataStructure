#pragma once
#include "CoreMinimal.h"

template<typename T>
struct TTreeNode
{
	template<typename T1>
	friend struct TBinaryTree;
	friend class UBinaryTreeStatics;

	T Data;

	const uint32 NodeName;

	S_PRIVATE(TTreeNode* LeftChild);

	S_PRIVATE(TTreeNode* RightChild);

	S_PRIVATE(TTreeNode* Parent);

	TTreeNode(uint32 inNodeName, const T& inData = T(0));

	TTreeNode(const TTreeNode& another);

	uint16 Degree() const;

	bool IsLeafNode() const;

	void AddNode(ETreeNodeChildDirection inChildNodeName, TTreeNode* inNode);
	
	~TTreeNode();

private:

	TTreeNode*& GetChildByEnum(ETreeNodeChildDirection inChildNodeName);
};

#include "TreeNode.inl"