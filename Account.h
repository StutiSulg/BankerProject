#pragma once
#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

const int ACCT_FUNDS = 10; 

class Account
{
	friend ostream& operator<<(ostream &outStream, const Account &acct); 
	
public:
	Account();
	Account(string name, int id); 
	~Account();

	bool setAmount(int acctType, int amount, char tranType, string transInfo); 
	int getAmount(int acctType) const;
	int getAccoutNum() const; 
	string getName() const; 
	
	void display() const; 
	void display(const int fundType); 
	void displayFundsHistory(); 

	void addErrorHistory(int acctType, string error); 

	bool deleteAcct(); 
	
private: 
	struct Funds
	{
		int amount; 
		queue<string> history; 		
	};

	Funds accountTypes[ACCT_FUNDS]; 
	string fundTypes[ACCT_FUNDS]; 
	string name; 
	int accountNum; 

};

