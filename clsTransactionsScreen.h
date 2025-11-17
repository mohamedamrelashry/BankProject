#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>

class clsTransactionsScreen : protected clsScreen  
{	private: 
	enum enTransactionsMenue{
		eDeposit = 1, eWithdraw = 2,
		eShowTotalBalance = 3,eShowTransferScreen = 4
		,eLogTransferScreen  = 5 , eShowMainMenue = 6 , 


	};

	static short _ReadTransactionsMenueOption() {
		cout << setw(37) << left << ""
			<< "Choose what do you want to do? [1 to 5]? ";
		short Choice =
			clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}
	static void _GoBackToTransactionsMenue() {
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowTransactionsMenue();

	}
	
	static void _ShowDepositScreen(){
	
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithDrawScreen(){
		clsWithdrawScreen::ShowDepositScreen();

	}
	static void _ShowTotalBalanceScreen(){
		clsTotalBalancesScreen::ShowTotalBalacesScreen();
	}
	static void _ShowTransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen() {

		clsTransferLogScreen::ShowTransferLogScreen();
	}
	static void _ShowMainMenueOptions() {

		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _performTransactionMenueOption(enTransactionsMenue TransMenueOption) {
		switch (TransMenueOption)
		{
		case clsTransactionsScreen::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eWithdraw:
			system("cls");
			_ShowWithDrawScreen(); 
			_GoBackToTransactionsMenue(); 
			break;
		case clsTransactionsScreen::eShowTotalBalance:
			system("cls");
			_ShowTotalBalanceScreen();
			_GoBackToTransactionsMenue();

			break;
		case clsTransactionsScreen::eShowTransferScreen:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eLogTransferScreen:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
		case clsTransactionsScreen::eShowMainMenue:

			break;
		
		}
	}
	public:
		static void ShowTransactionsMenue() {
			if (!CheckPermissionRights(clsUser::pTranactions)) {

				return;
			}

			system("cls");
			_DrawScreenHeader("\t  Transactions Screen");

			cout << setw(37) << left << "" << "===========================================\n";
			cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
			cout << setw(37) << left << "" << "===========================================\n";
			cout << setw(37) << left << "" << "\t[1] Deposit.\n";
			cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
			cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
			cout << setw(37) << left << "" << "\t[4] Transfer.\n";
			cout << setw(37) << left << "" << "\t [5] Log Transfer\n";
			cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
			cout << setw(37) << left << "" << "===========================================\n";
			
			_performTransactionMenueOption((enTransactionsMenue)_ReadTransactionsMenueOption());
		}
};

