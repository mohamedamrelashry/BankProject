#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <iostream>
class clsFindUserScreen : protected clsScreen 
{
private: 
    static void _PrintUser(clsUser Client) {
        cout << "\nUser Card:";
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
    static void ShowFindUserScreen() {
        _DrawScreenHeader("Update User Screen");
        string UserName = ""; 
        cout << "\nEnter UserName:";
        UserName = clsInputValidate::ReadString(); 
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nEnter UserName:";
            UserName = clsInputValidate::ReadString();

        }
        clsUser User = clsUser::Find(UserName);
        
        if (!User.IsEmpty()) {
            cout << "\nClient Found :-)\n";
        }
        else {
            cout << "\nClient Was not Found :-(\n";

        }
        _PrintUser(User); 

    }


};

