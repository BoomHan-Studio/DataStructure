#pragma once
#include "Statics.h"
#include "Structs/BinaryTree.h"

class UBinaryTreeStatics : UStatics
{
private:
	/**
	 *@brief 此类禁止构造。
	 */
	UBinaryTreeStatics() = delete;
	
public:

	/**
	 *@brief 以先序非递归方式创建一棵二叉树。
	 */
	template<typename T>
	static TBinaryTree<T>* CreateBinaryTree();

	/**
	 *@brief 输出二叉树的线序、中序、后续非递归下的结点访问次序。\n
	 *输出二叉树的按层次遍历序列。
	 */
	template<typename T>
	static void TraverseTree(TBinaryTree<T>* inTree);

	/**
	 *@brief 输出二叉树所有的叶子结点和叶子结点个数。
	 */
	template<typename T>
	static void PrintAllLeaves(TBinaryTree<T>* inTree);

	/**
	 *@brief 输出二叉树的高度。\n
	 *输出二叉树的形状。
	 */
	template<typename T>
	static void PrintTree(TBinaryTree<T>* inTree);

private:

	template<typename T>
	static void PrintTree(TTreeNode<T>* inNode, uint16 inHeight);
};

#include "BinaryTreeStatics.inl"