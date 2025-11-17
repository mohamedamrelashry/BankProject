#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <iostream>
class clsUpdateUserScreen:protected clsScreen
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
        cout << "\nDo you want to give access to :";
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

        cout << "n\ Manage Users Screen ? y/n? ";
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

    static void ShowUpdateUserScreen() {

        _DrawScreenHeader("Update User Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nPlease Enter client Account Number: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "\n\nUpdate User Info:";
        cout << "\n____________________\n";

        _ReadUserInfo(User);

        clsUser::enSaveResults  saveResult;
        saveResult = User.Save();


        switch (saveResult)
        {
        case clsUser::svSucceeded:
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintUser(User);
            break;
        case clsUser::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
};

