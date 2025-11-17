#pragma once
#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsFindClientScreen.h"
#include "clsManageUsersScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"


class clsMainScreen:protected clsScreen
{
private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7,eLoginRegister= 8,eCurrencyExchange =9 ,eExit = 10
    };

    static short _ReadMianMenueOption() {
        cout << setw(37) << left << "" 
            << "Choose what do you want to do? [1 to 10]? ";
        short Choice = 
            clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }
    static void _GoBackToMainMenue() {
        cout<< setw(37) << left << "" 
            << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenue();
    }
    static void _ShowAllClientsScreen() {

        clsClientListScreen::ShowClientsList();

    }
    static void _ShowAddNewClientsScreen() {

        clsAddNewClientScreen::ShowAddNewClientScreen();
    }
    static void _ShowDeleteClientsScreen() {

        clsDeleteClientScreen::showDeleteClientScreen();
    }
    static void _ShowUpdateClientsScreen() {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }
    static void _ShowFindClientScreen() {
        clsFindClientScreen::ShowFindClientScreen();

    }
    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();

    }
    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersScreen();

    }
    static void _ShowLoginRegisterScreen() {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }
    static void _ShowCurrenciesMenueScreen() {
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
    }

    static void _Logout() {

        CurrentUser = clsUser::Find("", "");
    }

    static void _performMainMenueOption(enMainMenueOptions MainMenueOption ) {
        switch (MainMenueOption)
        {
        case clsMainScreen::eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eDeleteClient:
            system("cls");
            _ShowDeleteClientsScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eUpdateClient:
            system("cls");
            _ShowUpdateClientsScreen();
            _GoBackToMainMenue();
            
            break;
        case clsMainScreen::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            
            break;
        case clsMainScreen::eManageUsers:
            
            system("cls");
            _ShowManageUsersMenue();
          
            break;
        case clsMainScreen::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break; 
        case clsMainScreen::eCurrencyExchange: 
            system("cls");
            _ShowCurrenciesMenueScreen();
            _GoBackToMainMenue();

        case clsMainScreen::eExit:
            system("cls");
            _Logout();
            break;
        }

    }

public:

    static void ShowMainMenue() {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currrency Exchange\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performMainMenueOption((enMainMenueOptions)_ReadMianMenueOption());
    }

};

