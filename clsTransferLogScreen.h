#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include"clsBankClient.h";
#include <iomanip>
#include <iostream>
using namespace std; 
class clsTransferLogScreen: protected clsScreen
{
private:
    static void _PrintTransferLoginRecordLine(clsBankClient::stTransferLogin
        TransferLoginRecord)
    {  
        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLoginRecord.Date;
        cout << "| " << setw(10) << left << TransferLoginRecord.sAccountNumber;
        cout << "| " << setw(10) << left << TransferLoginRecord.dAccountNumber;
        cout << "| " << setw(15) << left << TransferLoginRecord.Amount;
        cout << "| " << setw(15) << left << TransferLoginRecord.sBalance;
        cout << "| " << setw(15) << left << TransferLoginRecord.dBalance;
        cout << "| " << setw(10) << left << TransferLoginRecord.UserName;


    
    }

public:

	static void ShowTransferLogScreen() {

        vector <clsBankClient::stTransferLogin> vUsers;
        vUsers = clsBankClient::GetTransferLoginList();
        string Title = "\t Transfer Log Screen";
        string substitle = " \tUser List (" + to_string(vUsers.size()) + ") Record(s).";
        _DrawScreenHeader(Title, substitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Acct";
        cout << "| " << left << setw(10) << "d.Acct";
        cout << "| " << left << setw(15) << "Amount ";
        cout << "| " << left << setw(15) << "S.Balance";
        cout << "| " << left << setw(15) << "d.Balance";
        cout << "| " << left << setw(10) << "User ";
        
        
        
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient::stTransferLogin user : vUsers)
            {
                _PrintTransferLoginRecordLine(user);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
	
};

