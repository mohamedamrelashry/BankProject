#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"


class clsFindCurrencyScreen:clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";

	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}



public: 
	static void ShowFindCurrencyScreen() {
		_DrawScreenHeader("Find Currency Screen ");
		cout << "Find By: (1) Code or (2) Country :?\n";
		short Answer = clsInputValidate::ReadShortNumberBetween(1, 2);
		if (Answer == 1) {
			cout << "Enter Currency Code : \n"; 
			string CurrencyCode= clsInputValidate::ReadString();
			while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
				cout << "Currency is not found, chose another one : \n";
				CurrencyCode = clsInputValidate::ReadString();

			}
			
			clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else{
			cout << "Enter Currency Code:\n";
			string CurrencyCode = clsInputValidate::ReadString();
			while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
				cout << "Currency is not found, chose another one :\n ";
				CurrencyCode = clsInputValidate::ReadString();

			}
			clsCurrency Currency = clsCurrency::FindByCountry(CurrencyCode) ;
			_ShowResults(Currency);
		}

	}
};

