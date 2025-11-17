#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateCurrencyRateScreen : protected clsScreen 
{

private:
	static float _ReadRate()
	{
		cout << "\nEnter New Rate: ";
		float NewRate = 0;

		NewRate = clsInputValidate::ReadDblNumber();
		return NewRate;
	}

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
	static void ShowUpdateCurrencyRateScreen() {
		_DrawScreenHeader("Update Currency Rate Screen");
		cout << "Enter Currency Code? ";
		string CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "Currency is not found, chose another one : ";
			CurrencyCode = clsInputValidate::ReadString();

		}
		clsCurrency Currency = 
			clsCurrency::FindByCurrencyCode(CurrencyCode);
		_PrintCurrency(Currency);
		
		char Answer ;
		cout << "Do you want Change rate y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			cout << "\n\nUpdate Currency Rate:";
			cout << "\n____________________\n";
			
			Currency.UpdateRate(_ReadRate());
			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);

		}


	}


};

