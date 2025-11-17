#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <iostream>


class clsTransferScreen : clsScreen
{
private: 
    static void _printClient(clsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }
    static float ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadDblNumber();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }
public: 
	static void ShowTransferScreen() {
        _DrawScreenHeader("\t Transfer screen ");

        char Answer = 'n';
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number to Tranfer from: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\n Account number is not found, choose another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient SourceClient = clsBankClient::Find(AccountNumber);
        _printClient(SourceClient);


        cout << "\nPlease Enter client Account Number to Tranfer To: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\n Account number is not found, choose another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient DestinationClient = clsBankClient::Find(AccountNumber);
        _printClient(DestinationClient);


        cout << "please, enter Tranfer amount?";
        double Amount = ReadAmount(SourceClient);
        cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }
        _printClient(SourceClient);
        _printClient(DestinationClient);

    }

};

