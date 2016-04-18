// MainBank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fstream"
#include "Banker.h"
#include <string>
#include <iostream>
using namespace std; 

int main()
{
	string bankTransln = "BankTransln.txt"; 
	
	Banker Chase("BankTransln.txt");
	Chase.runTransactions(); 
	Chase.displayFinal(); 

	return 0;
}

