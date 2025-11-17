#pragma once
#include "clsScreen.h"
#include "clsUser.h"

#include "clsInputValidate.h"
#include <iomanip>
#include <iostream>
class clsDeleteUserScreen : protected clsScreen
{

private: 
    static void _PrintUser(clsUser Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.UserName;
        cout << "\nPassword    : " << Client.Password;
        cout << "\nPermission     : " << Client.Permissions;
        cout << "\n___________________\n";


    }
public: 
    static void showDeleteClientScreen() {

        _DrawScreenHeader("Delete User Screen");

        string UserName = "";
        cout << "\nPlease Enter client Account Number: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName)) {
            cout << "\n Account number is not found, choose another one : ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);


        char Ans = 'n';
        cout << "Are you sure you want to delete this client y/n?";
        cin >> Ans;
        if (Ans == 'y' || Ans == 'Y') {

            if (User.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintUser(User);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }

        }

    }

};

