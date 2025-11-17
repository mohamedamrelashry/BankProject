#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include <iomanip>
class clsDepositScreen: protected clsScreen
{
private:

    static void _printClient(clsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public: 
	static void ShowDepositScreen() {
        _DrawScreenHeader("\t Deposit screen ");


        char Answer = 'n';
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\n Account number is not found, choose another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _printClient(Client1);
        
            cout << "please, enter deposit amount?";
            double Amount = clsInputValidate::ReadDblNumber();
            cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Client1.Deposit(Amount);

                cout << "\nAmount Deposited Successfully.\n";
                cout << "\nNew Balance Is: " << Client1.AccountBalance;

            }
            else
            {
                cout << "\nOperation was cancelled.\n";
            }


	}
};

