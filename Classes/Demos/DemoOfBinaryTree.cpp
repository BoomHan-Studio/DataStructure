#include "DemoOfBinaryTree.h"

#include "FunctionLibrarys/BinaryTreeStatics.h"

ADemoOfBinaryTree::ADemoOfBinaryTree()
	:ADemo(),
	charTree(nullptr)
{
	demoName = "二叉树的相关操作演示";
}

void ADemoOfBinaryTree::BeginPlay()
{
	ADemo::BeginPlay();

	charTree = UBinaryTreeStatics::CreateBinaryTree<ELEMENT_TYPE>();
	if (!charTree)
	{
		cout << "你创建了空二叉树。" << endl;
	}
	else
	{
		UBinaryTreeStatics::PrintTree(charTree);
		UBinaryTreeStatics::TraverseTree(charTree);
		UBinaryTreeStatics::PrintAllLeaves(charTree);
	}
}

ADemoOfBinaryTree::~ADemoOfBinaryTree()
{
	delete charTree;
}
