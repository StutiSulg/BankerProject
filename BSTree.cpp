#include "stdafx.h"
#include "BSTree.h"


BSTree::BSTree()
{
	root = nullptr; 
}

bool BSTree::Insert(Account *actPtr)
{
	Node *newAct = new Node();
	newAct->pAcct = actPtr;

	root = insertInOrder(root, newAct); 
	if (root == nullptr)
	{
		return false; 
	}

	return true; 


}

BSTree::Node* BSTree::insertInOrder(Node* subTreePtr, Node* newNodePtr)
{
	if (subTreePtr == nullptr)
	{
		return newNodePtr; 
	}
	else if (subTreePtr->pAcct->getAccoutNum() > newNodePtr->pAcct->getAccoutNum())
	{
		Node *temp; 
		temp = insertInOrder(subTreePtr->left, newNodePtr); 
		subTreePtr->left = temp; 
	}
	else
	{
		Node *temp;
		temp = insertInOrder(subTreePtr->right, newNodePtr);
		subTreePtr->right = temp;
	}
}

bool BSTree::Retrieve(const int &id, Account *&acctPtr) const
{
	Node *foundAcct; 
	foundAcct = findNode(root, id); 

	if (foundAcct == NULL)
	{
		acctPtr = nullptr;
		return false;
	}
	else
	{
		acctPtr = foundAcct->pAcct; 
		return true;
	}	

	 
}

BSTree::Node* BSTree::findNode(Node* treePtr, const int &id) const
{
	if (treePtr == nullptr)
	{
		return nullptr; 
	}
	else if (treePtr->pAcct->getAccoutNum() == id)
	{
		return treePtr; 
	}
	else if (treePtr->pAcct->getAccoutNum() > id)
	{
		return findNode(treePtr->left, id); 
	}
	else
	{
		return findNode(treePtr->right, id); 
	}
}

void BSTree::Display() const
{
	traverse(root); 
}

void BSTree::traverse(Node *treePtr) const
{
	if (treePtr != nullptr)
	{
		traverse(treePtr->left); 
		cout << *(treePtr->pAcct);
		traverse(treePtr->right); 
	}
	
}

void BSTree::Empty()
{
	clearTraverse(root); 
	root = nullptr; 
}

void BSTree::clearTraverse(Node *treePtr) const
{
	if (treePtr == nullptr)
	{
		return; 
	}

	clearTraverse(treePtr->left); 
	clearTraverse(treePtr->right);

	if (treePtr->left == nullptr && treePtr->right == nullptr)
	{
		treePtr->pAcct->deleteAcct();
			treePtr->pAcct = nullptr; 
			treePtr->left = nullptr; 
			treePtr->right = nullptr; 
			delete treePtr;
			treePtr = nullptr; 
	}

}

bool BSTree::isEmpty() const
{
	if (root == nullptr)
	{
		return true;
	}

	return false; 
}

BSTree::~BSTree()
{
}
