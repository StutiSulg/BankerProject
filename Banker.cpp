#include "stdafx.h"
#include <fstream> 
#include "Banker.h"
#include <string>
#include <iostream>
using namespace std; 

Banker::Banker()
{
}

Banker::Banker(string fileName)
{
	std::string line; 
	ifstream file(fileName); 
	if (file.is_open())
	{
		while (getline(file, line))
		{	
			tranQ.push(Transaction(line)); 
		}
	}
}

void Banker::runTransactions()
{
	while (tranQ.empty() != true)
	{		
		tranQ.front().runTran(customer); 
		tranQ.pop();		
	}
}

void Banker::displayFinal() const
{
	customer.Display(); 
}

Banker::~Banker()
{
}
