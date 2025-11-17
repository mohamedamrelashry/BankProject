#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <iostream>
class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User) {

        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission ";
        User.Permissions = _ReadPermission();
    }
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
    static int _ReadPermission() {
        int Permissioin = 0; 
        char Answer = 'n';
        
        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1; 
        }
        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
      
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissioin += clsUser::enPermissions::pListCleints;
        }

        cout << "\nShow Add new Client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissioin += clsUser::enPermissions::pAddNewClient;
        }
        cout << "\nShow Delete Client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissioin += clsUser::enPermissions::pDeleteClient;
        }
        cout << "\nShow Update Client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissioin += clsUser::enPermissions::pUpdateClient;
        }
        cout << "\nShow Find Client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissioin += clsUser::enPermissions::pFindClient;
        }

        cout << "n\ Transaction ? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissioin += clsUser::enPermissions::pTranactions;
        }
        
        cout << "\n Manage Users Screen ? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissioin += clsUser::enPermissions::pManageUsers;
        }
        cout << "\n Login Register Screen ? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissioin += clsUser::enPermissions::pLoginList;
        }
        return Permissioin;

    }
public: 
    static void ShowAddNewUserScreen() {
        _DrawScreenHeader("Show Add New User Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }

 



};

