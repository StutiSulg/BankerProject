#pragma once
#include <string>
#include <vector>
#include "BSTree.h"
#include <iostream>
using namespace std;

class Transaction
{
	const int ACCT_LENGTH = 4; 
	
public:
	Transaction();
	Transaction(string Task); 
	~Transaction();

	void runTran(BSTree &customer); 

private: 

	enum tranNameType
	{
		OPEN = 'O',
		DEPOSIT = 'D',
		WITHDRAW = 'W',
		TRANSFER = 'T',
		HISTORY = 'H'		
	};
	enum TransferableFundTypes
	{
		MoneyMarket, 
		PrimeMoneyMarket, 
		LongTermBond, 
		ShortTermBond, 
	};

	string name;
	int amount; 
	char tranType;
	//Primary Account information
	int accountNumber;	 
	int fundType;
	//Secondary Account information
	int accountTranNum;
	int fundTranType;
	//If extrawithdrawal is needed
	int extraFundWithdraw;
	int extraWithdraw;  
	
	//divides the transaction string into correct paramater
	void findInfo(string info); 
	//checks for errors before transactions began
	bool checkError(BSTree customer); 
	//produces the correct error message
	bool produceMessage(int acct1, int acct2, Account *&temp, BSTree &customer); 
	//prints that error message
	void printErrorMess(Account *temp, BSTree &customer); 

	//calls the correct transaction method
	void callTransactionMethod(); 

	void openAccount(BSTree &customer);
	void deposit(BSTree &customer);
	void withdraw(BSTree &customer);
	void transfer(BSTree &customer);
	void history(BSTree &customer);

};

