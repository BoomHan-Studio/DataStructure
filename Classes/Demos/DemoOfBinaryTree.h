#pragma once
#include "Demo.h"

#define ELEMENT_TYPE int

class ADemoOfBinaryTree : public ADemo
{
public:
	
	ADemoOfBinaryTree();

	virtual void BeginPlay() override;

	virtual ~ADemoOfBinaryTree() override;

private:

	using FCharBinaryTree = TBinaryTree<ELEMENT_TYPE>;
	FCharBinaryTree* charTree;
};