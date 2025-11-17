#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include <iostream>
class clsLoginRegisterScreen:clsScreen
{
private:
   
    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
    }
   


public:
	static void ShowLoginRegisterScreen() {
        if (!CheckPermissionRights(clsUser::pLoginList)) {
            return;
        }
        vector <clsUser::stLoginRegisterRecord> vUsers;
        vUsers = clsUser::GetLoginRegisterList();
        string Title = "\t Login Register Screen";
        string substitle = " \tUser List (" + to_string(vUsers.size()) + ") Client(s).";
        _DrawScreenHeader(Title, substitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord user : vUsers)
            {
                _PrintLoginRegisterRecordLine(user);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

	 
};

