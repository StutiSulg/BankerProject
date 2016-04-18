#pragma once
#include "Account.h"
#include <string>
#include <iostream>
using namespace std; 

class BSTree
{
public:
	BSTree();
	~BSTree();
	bool Insert(Account *acctPtr);
	// retrieve object, first parameter is the ID of the account
	// second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int &, Account * &) const;
	// displays the contents of a tree to cout
	void Display() const;
	void Empty();
	bool isEmpty() const;

	
private:
	struct Node
	{
		Account *pAcct;
		Node *right;
		Node *left;
	};
	Node *root;

protected:
	Node* insertInOrder(Node* subTreePtr, Node* newNode); 
	Node* findNode(Node* treePtr, const int &id) const; 
	void traverse(Node* treePtr) const; 
	void clearTraverse(Node *treePtr) const; 

};

