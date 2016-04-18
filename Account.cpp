#include "stdafx.h"
#include "Account.h"



Account::Account()
{
	name = ""; 
	accountNum = NULL; 
}

Account::Account(string accName, int id)
{
	name = accName; 
	accountNum = id; 
	for (int i = 0; i < ACCT_FUNDS; i++)
	{
		accountTypes[i].amount = 0; 
	}
	
	string fundName[ACCT_FUNDS] = { "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", 
		"500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index" };
	for (int i = 0; i < ACCT_FUNDS; i++)
	{
		fundTypes[i] = fundName[i]; 
	}
}

int Account::getAccoutNum() const
{
	return accountNum; 
}

string Account::getName() const
{
	return name; 
}

int Account::getAmount(int acctType) const
{
	return accountTypes[acctType].amount; 
}

void Account::addErrorHistory(int acctType, string error)
{
	accountTypes[acctType].history.push(error); 
}

void Account::display() const
{
	cout << name + " Account ID: "; 
	cout << accountNum << endl;

	for (int i = 0; i < ACCT_FUNDS; i++)
	{
		cout << "    " << fundTypes[i] + ": $"; 
		cout << accountTypes[i].amount << endl;
	}
}

void Account::display(const int fundType) 
{
	cout << "    History of " + fundTypes[fundType] + ": ";
	cout << "$" << accountTypes[fundType].amount << endl;

	queue<string> temp;

	while (!accountTypes[fundType].history.empty())
	{
		string info = accountTypes[fundType].history.front(); 
		cout << "    " + info << endl;
		accountTypes[fundType].history.pop(); 
		temp.push(info); 
		
	}

	while (!(temp.empty()))
	{		
		string tempPlace =temp.front(); 
		accountTypes[fundType].history.push(tempPlace);
		temp.pop();
	}

	cout << endl; 

}

void Account::displayFundsHistory()
{
	for (int i = 0; i < ACCT_FUNDS; i++)
	{
		display(i); 
	}

}

bool Account::setAmount(int acctType, int amount, char tranType, string transInfo)
{
	accountTypes[acctType].amount += amount; 
	string stranType(1, tranType); 
	string info = stranType + " " + to_string(accountNum) + " " + to_string(amount); 
	if (tranType == 'T')
	{
		accountTypes[acctType].history.push(transInfo); 
	}
	else
	{
		accountTypes[acctType].history.push(info); 
	}
	
	return true; 
}

bool Account::deleteAcct()
{
	name = ""; 
	accountNum = NULL; 
	for (int i = 0; i < ACCT_FUNDS; i++)
	{
		accountTypes[i].amount = 0; 
		accountTypes[i].history.empty(); 
	}
	return true;
}

ostream& operator<<(ostream &outStream, const Account &acct)
{
	acct.display(); 
	return outStream; 
}


Account::~Account()
{
}
