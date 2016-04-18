# BankerProject

Purpose: 

Design: 

There are four main classes the Banker class, Transaction class, Account class, and Funds class. 

Program starts off at the Main calss and reads the reading the test file and giving the whole test file to the Banker object. 
Then the Banker object takes the text file and reads each individual line placing it into a queue. 
The Banker runs through the queue passes it to the Transaction Class.

The Transaction class then breaks the transaction command and calls on the correct method to carry out the transaction. 
These methods would be open, deposit, withdraw, transfer, and display history. 
The private section of this class contains: the customer binary tree, account number, and deposit amount. 
Inside each method the correct Account is pulled from the binary tree and the correct method is called of the 
Account to manipulate the correct fund. The account’s method is passed the amount (if available).

The Account object has-a relationship with ten fund objects. 
The Fund class has private data such as amount and history. 
This way when accounts have to print the history each fund object has kept track of its own amount.

 
