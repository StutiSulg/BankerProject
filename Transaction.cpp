#include "stdafx.h"
#include "Transaction.h"
#include <sstream>


Transaction::Transaction()
{
	fundType = -1;
	fundTranType = -1;
	accountNumber = -1;
	accountTranNum = -1;
	extraWithdraw = -1;
	extraFundWithdraw = -1;
	tranType = ' ';
}

Transaction::Transaction(string task)
{
	fundType = -1; 
	fundTranType = -1;
	accountNumber = -1; 
	accountTranNum = -1; 
	extraWithdraw = -1; 
	extraFundWithdraw = -1; 
	tranType = ' '; 
	
	queue<string> strings; 
	istringstream f(task); 
	string s; 
	while (getline(f, s, ' '))
	{		
		strings.push(s); 
	}
	tranType = strings.front().c_str()[0];
	strings.pop();

	if (tranType == OPEN)
	{
		string first = strings.front(); 
		strings.pop(); 
		string last = strings.front(); 
		strings.pop(); 
		name = first + " " + last; 
		accountNumber = stoi(strings.front()); 
		strings.pop(); 
	}
	else if (tranType == HISTORY)
	{
		string num = strings.front(); 
		strings.pop();
		findInfo(num); 
	}
	else if (tranType == TRANSFER)
	{
		string num1 = strings.front();
		strings.pop();
		findInfo(num1); 
		
		amount = stoi(strings.front());
		strings.pop();
		
		string num2 = strings.front();
		strings.pop();
		findInfo(num2); 
	}
	else
	{
		string num = strings.front();
		strings.pop();
		findInfo(num); 
		amount = stoi(strings.front()); 
		strings.pop(); 
	}

	 

}

void Transaction::runTran(BSTree &customer)
{
	if (tranType == OPEN)
	{
		openAccount(customer); 
	}
	else if (tranType == HISTORY)
	{
		history(customer); 
	}
	else if (tranType == TRANSFER)
	{
		transfer(customer); 
	}
	else if (tranType == WITHDRAW)
	{
		withdraw(customer); 
	}
	else if (tranType == DEPOSIT)
	{
		deposit(customer); 
	}
}

void Transaction::openAccount(BSTree &customer)
{
	Account *temp; 
	 
	if (customer.Retrieve(accountNumber, temp))
	{
		cerr << "ERROR: Account " << accountNumber << " is already open. Transaction Refused" << endl;
		temp = NULL; 
		delete temp; 
		return; 
	}

	if (to_string(accountNumber).length() != ACCT_LENGTH)
	{
		cerr << "ERROR: Account " << accountNumber << " is an invalid number. Transaction Refused" << endl;
		temp = NULL;
		delete temp;
		return;
	}
	Account *acctPTr = new Account(name, accountNumber); 
	customer.Insert(acctPTr); 
	acctPTr = NULL;
	delete acctPTr; 
}

void Transaction::history(BSTree &customer)
{
	if (checkError(customer))
	{
		return; 
	} 
	Account *acctPtr; 
	customer.Retrieve(accountNumber, acctPtr); 

	cout << "Transaction History for " + acctPtr->getName(); 

	if (fundType >= 0)
	{
		cout << " of a specific Fund: " << endl; 
		acctPtr->display(fundType); 
	}
	else
	{
		cout << " by Funds: " << endl; 
		acctPtr->displayFundsHistory(); 
	}

	acctPtr = nullptr; 
	delete acctPtr; 
}

void Transaction::withdraw(BSTree &customer)
{
	if (checkError(customer))
	{
		return;
	}

	Account *acctPtr; 
	customer.Retrieve(accountNumber, acctPtr); 
	
	if (extraWithdraw > NULL)
	{
		acctPtr->setAmount(extraFundWithdraw, -extraWithdraw, tranType, "");
		acctPtr->setAmount(fundType, extraWithdraw, DEPOSIT, "");
	}

	acctPtr->setAmount(fundType, -amount, tranType, "");

	acctPtr = nullptr;
	delete acctPtr;
}

void Transaction::deposit(BSTree &customer)
{
	if (checkError(customer))
	{
		return;
	}

	Account *acctPtr; 
	customer.Retrieve(accountNumber, acctPtr); 
	acctPtr->setAmount(fundType, amount, tranType, ""); 

	acctPtr = nullptr;
	delete acctPtr;
}

void Transaction::transfer(BSTree &customer)
{
	if (checkError(customer))
	{
		return;
	}

	//History Info
	string temp(1, tranType); 
	string tranInfoHis = temp + " " + to_string(accountNumber) + "" + to_string(fundType) + " " +
					to_string(amount) + " " + to_string(accountTranNum) + "" + to_string(fundTranType);
	
	Account *acctPtr; 
	customer.Retrieve(accountNumber, acctPtr); 
	if (extraWithdraw > NULL)
	{
		
		acctPtr->setAmount(extraFundWithdraw, -extraWithdraw, WITHDRAW, "");
		acctPtr->setAmount(fundType, extraWithdraw, DEPOSIT, "");
	}
	acctPtr->setAmount(fundType, -amount, tranType, tranInfoHis); 
	
	acctPtr = nullptr;
	delete acctPtr;

	Account *acctPtrTran; 
	customer.Retrieve(accountTranNum, acctPtrTran); 
	acctPtrTran->setAmount(fundTranType, amount, tranType, tranInfoHis); 

	acctPtrTran = nullptr;
	delete acctPtrTran;
}

void Transaction::findInfo(string info)
{
	string accountNum; 
	if (info.length() > ACCT_LENGTH)
	{
		accountNum = info.substr(0, info.length() - 1);
	}
	else
	{
		accountNum = info.substr(0, info.length()); 
	}
	
	if (accountNumber < NULL)
	{
		accountNumber = atoi(accountNum.c_str());
	}
	else
	{
		accountTranNum = atoi(accountNum.c_str());
	}
	
	if (info.length() > ACCT_LENGTH && fundType <  NULL)
	{
		string temp = info.substr(info.length() - 1, info.length());
		fundType = atoi(temp.c_str());
	}
	else
	{
		if (info.length() > ACCT_LENGTH)
		{
			string temp = info.substr(info.length() - 1, info.length());
			fundTranType = atoi(temp.c_str());
		}
		else
		{
			fundType = -1; 
		}		
	}
	
}

bool Transaction::checkError(BSTree customer)
{
	Account *temp;
	

	if (!customer.Retrieve(accountNumber, temp))
	{
		cerr << "ERROR: Account " << accountNumber << " was not found. Transaction Refused" << endl;
		temp = NULL;
		delete temp;
		return true;
	}
	
	if ((accountTranNum > 0 && !customer.Retrieve(accountTranNum, temp)))
	{
		cerr << "ERROR: Account " << accountTranNum << " was not found. Transaction Refused" << endl;
		temp = NULL;
		delete temp;
		return true;
	}

	if (to_string(accountNumber).length() != ACCT_LENGTH || to_string(accountTranNum).length() != ACCT_LENGTH &&  accountTranNum >= NULL)
	{
		if (to_string(accountNumber).length() != ACCT_LENGTH - 1 )
		{
			cerr << "ERROR: Account " << accountNumber << fundType << " was not found. Transaction Refused" << endl;
		}
		if (accountTranNum != -1)
		{
			cerr << "ERROR: Account " << accountNumber << fundTranType << " was not found. Transaction Refused" << endl;
			
		}		
		
		temp = NULL;
		delete temp;
		return true;
	}

	if (amount > temp->getAmount(fundType) && (tranType == WITHDRAW || tranType == TRANSFER))
	{
		if (fundType == MoneyMarket)
		{
			if (produceMessage(MoneyMarket, PrimeMoneyMarket, temp, customer))
			{
				return true;
			}

			return false; 
		}
		else if (fundType == PrimeMoneyMarket)
		{
			if (produceMessage(PrimeMoneyMarket, MoneyMarket, temp, customer))
			{
				return true;
			}

			return false;
		}		
		else if (fundType == ShortTermBond)
		{
			if (produceMessage(ShortTermBond, LongTermBond, temp, customer))
			{
				return true;
			}

			return false;
		}
		else if (fundType == LongTermBond)
		{
			if (produceMessage(LongTermBond, ShortTermBond, temp, customer))
			{
				return true;
			}
			return false;
		}
		else
		{
			printErrorMess(temp, customer); 
			temp = NULL;
			delete temp;
			return true;
		}

		
	}
		
	return false; 
}
 
bool Transaction::produceMessage(int acct1, int acct2, Account *&temp, BSTree &customer)
{
	if (amount > ( temp->getAmount(acct2) + temp->getAmount(acct1)))
	{
		printErrorMess(temp, customer); 		
		temp = NULL;
		delete temp;
		return true;
	}

	extraFundWithdraw = acct2;
	extraWithdraw = amount - temp->getAmount(acct1); 
	temp = NULL;
	delete temp;
	return false;
}

void Transaction::printErrorMess(Account *temp, BSTree &customer)
{
	string fundNames[] = { "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond",
		"500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index" };

	cerr << "ERROR: Account " << accountNumber << " can NOT withdraw " << amount << " from the " << fundNames[fundType] << "." << endl;
	string stranType(1, tranType);
	string error;
	
	if (tranType == WITHDRAW)
	{
		error = stranType + " " + to_string(accountNumber) + " " + to_string(amount) + " (FAILED)";
	}
	else
	{
		error = stranType + " " + to_string(accountNumber) + to_string(fundType) + " " + 
			to_string(amount) + " " + to_string(accountTranNum) + to_string(fundTranType) + " (FAILED)";
		Account *temp2;
		customer.Retrieve(accountTranNum, temp2);
		temp2->addErrorHistory(fundTranType, error);
		temp2 = NULL;
		delete temp2;
	}

	temp->addErrorHistory(fundType, error);
}

Transaction::~Transaction()
{
}
