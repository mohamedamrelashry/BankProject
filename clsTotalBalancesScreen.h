#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsUtil.h "
#include <iomanip>


class clsTotalBalancesScreen : protected clsScreen 
{

private: 
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }

public:
    
    static void ShowTotalBalacesScreen() {
        vector <clsBankClient> vClients;
        vClients = clsBankClient::GetClientList();
        string Title = "\t Total Balance Screen";
        string substitle = " \t Client List (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, substitle);
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance" << endl;
        for (clsBankClient Client : vClients) {

            _PrintClientRecordBalanceLine(Client);
            cout << endl;
        }
        float TotalBalances = clsBankClient::GetTotalBalances();
        cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
        cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";
    
    }

};

