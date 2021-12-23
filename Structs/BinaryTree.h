#pragma once
#include "CoreMinimal.h"
#include "TreeNode.h"

template<typename T>
struct TBinaryTree
{
	using FTreeNode = TTreeNode<T>;
	friend class UBinaryTreeStatics;

	FTreeNode* Root/*根结点*/;

	S_PRIVATE(uint32 totalNodes)/*总共结点*/;

	explicit TBinaryTree(FTreeNode* inRoot);

	explicit TBinaryTree(const T& inData = T(0));

	~TBinaryTree();

	TBinaryTree(const TBinaryTree& another) = delete;
	TBinaryTree& operator =(const TBinaryTree& another) = delete;
	
	FORCEINLINE uint16 Height() const noexcept;
	
	void AddNode(uint32 inTargetNodeName, const T& inValue, ETreeNodeChildDirection inChildNodeName, bool& outAddSuccess);

	void DeleteNode(uint32 inDeleteNodeName, bool& outDeleteSuccess);

	FTreeNode* FindNode(uint32 inTargetNodeName);

	template<typename FunctionType>
	void ForEach(FunctionType inFunction, EBinaryTreeTraverseMethod inMethod);

	template<typename FunctionType, typename BreakType>
	void ForEachWithBreak(FunctionType inFunction, BreakType inBreakCondition, EBinaryTreeTraverseMethod inMethod);

private:

	void AddNode(FTreeNode* inTargetNode, const T& inValue, ETreeNodeChildDirection inChildNodeName, bool& outAddSuccess);
	
	void DeleteNode(const FTreeNode* inDeleteNode, bool& outDeleteSuccess);
	
	template<typename FunctionType>
	void ForEachNode(FunctionType inFunction, EBinaryTreeTraverseMethod inMehod = Sequence, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType, typename BreakType>
	void ForEachNodeWithBreak(FunctionType inFunction, BreakType inBreakCondition, EBinaryTreeTraverseMethod inMehod = Sequence, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType>
	void SequenceTraverse(FunctionType inFunction, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType>
	void SecondaryTraverse(FunctionType inFunction, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType>
	void RearTraverse(FunctionType inFunction, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType>
	void LevelTraverse(FunctionType inFunction, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType, typename BreakType>
	void SequenceTraverseWithBreak(FunctionType inFunction, BreakType inBreakCondition, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType, typename BreakType>
	void SecondaryTraverseWithBreak(FunctionType inFunction, BreakType inBreakCondition, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType, typename BreakType>
	void RearTraverseWithBreak(FunctionType inFunction, BreakType inBreakCondition, FTreeNode* inBeginNode = nullptr);

	template<typename FunctionType, typename BreakType>
	void LevelTraverseWithBreak(FunctionType inFunction, BreakType inBreakCondition, FTreeNode* inBeginNode = nullptr);

	uint16 Height(FTreeNode* inNode) const noexcept;
};

#include "BinaryTree.inl"