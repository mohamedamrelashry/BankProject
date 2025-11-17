#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsDeleteClientScreen: protected clsScreen
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
	static void showDeleteClientScreen() {
        if (!CheckPermissionRights(clsUser::pDeleteClient)) {

            return;
        }

        _DrawScreenHeader("Delete Client Screen");
        
        string AccountNumber = "";
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\n Account number is not found, choose another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _printClient(Client1);


        char Ans = 'n';
        cout << "Are you sure you want to delete this client y/n?";
        cin >> Ans;
        if (Ans == 'y' || Ans == 'Y') {

            if (Client1.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _printClient(Client1);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }

        }

	}

};

