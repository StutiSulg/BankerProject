#pragma once
#include <queue>
#include "Transaction.h"
#include "BSTree.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Banker
{
public:
	Banker();
	Banker(string transactionOrder); 
	~Banker();

	void runTransactions(); 
	void displayFinal() const; 

private: 
	BSTree customer;
	queue<Transaction> tranQ; 
	

};

