#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsAddNewClientScreen:protected clsScreen
{
private:
   static void _ReadClientInfo(clsBankClient& Client) {

       cout << "\nEnter FirstName: ";
       Client.FirstName = clsInputValidate::ReadString();

       cout << "\nEnter LastName: ";
       Client.LastName = clsInputValidate::ReadString();

       cout << "\nEnter Email: ";
       Client.Email = clsInputValidate::ReadString();

       cout << "\nEnter Phone: ";
       Client.Phone = clsInputValidate::ReadString();

       cout << "\nEnter PinCode: ";
       Client.PinCode = clsInputValidate::ReadString();

       cout << "\nEnter Account Balance: ";
       Client.AccountBalance = clsInputValidate::ReadDblNumber();
    }
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
	static void ShowAddNewClientScreen(){
        if (!CheckPermissionRights(clsUser::pAddNewClient)) {
        
            return;
        }
        
        
        _DrawScreenHeader("\t Add New Client Screen");
        string AccountNumber = "";
    cout << "\nPlease Enter client Account Number: ";

    AccountNumber = clsInputValidate::ReadString();
    while (clsBankClient::IsClientExist(AccountNumber)) {
        cout << "\nAccount Number Is Already Used, Choose another one: ";
        AccountNumber = clsInputValidate::ReadString();

    }
    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

    _ReadClientInfo(NewClient);


    clsBankClient::enSaveResults  saveResult;
    saveResult = NewClient.Save();


    switch (saveResult)
    {
    case clsBankClient::svSucceeded:
        cout << "\nAccount Addedd Successfully :-)\n";
        NewClient.Print();
        break;
    case clsBankClient::svFaildEmptyObject:
        cout << "\nError account was not Added";
        break;
    case clsBankClient::enSaveResults::svFaildAccountNumberExists:
    {
        cout << "\nError account was not saved because account number is used!\n";
        break;

           }
        }
	}

};

