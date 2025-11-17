#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include"clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include <iomanip>
#include <iostream>

class clsLoginScreen : clsScreen 
{
private:

	static bool _Login() {
		bool LogainFaild = 0 ;
		int FailedTrials = 0;
		string Username ="", Password = "";
		do{
			if (LogainFaild) {
				FailedTrials++;
				cout << "\n Invalid UserName/Password!\n\n";
				cout << "You have " << ( 3 - FailedTrials) << " trails remained \n\n";

				
			}
			if (FailedTrials == 3) {
				
				cout << "\n You are Locked after 3 failed Trails";
				return false; 
			}
			cout << "Enter Username? ";
			cin >> Username;

			cout << "Enter Password? ";
			cin >> Password;
			CurrentUser = clsUser::Find(Username, Password);
			LogainFaild = CurrentUser.IsEmpty() ; 
		} while (LogainFaild);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
	}
public: 
	static bool ShowLoginScreen() {
		
		
		system("cls"); 
		_DrawScreenHeader("Loging Screen");
		return _Login();
	}

};

