#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
#include "clsString.h"

using namespace std;

class clsInputValidate
{	public: 

	static bool IsNumberBetween(short Number, short From, short To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}
	static bool IsNumberBetween(int number ,int from,int to) {
		return (number > from && number < to);
	}
	static bool IsNumberBetween(float number, float from, float to) {
		return (number > from && number < to);
	}
	static bool IsNumberBetween(double number, double from, double to) {
		return (number > from && number < to);
	}
	static bool IsDateBetween(clsDate Date , clsDate sDate  ,clsDate eDate) {
		if (!clsDate::IsDate1BeforeDate2(sDate, eDate))
			clsDate::Swap(sDate, eDate);
		if ((clsDate::IsDate1BeforeDate2(sDate, Date) ||clsDate::IsDate1EqualDate2(sDate,Date)) &&
			(clsDate::IsDate1BeforeDate2(Date, eDate) || clsDate::IsDate1EqualDate2(eDate, Date)))
			return true;
		return false;
	}


	static int ReadIntNumber(string err ="Invalid Number, Enter again\n") {
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << err;
		}
		return Number;
	}
	static int ReadIntNumberBetween(int from, int to, string err = "Number is not within range, Enter again:\n") {
		int Number = ReadIntNumber();
		
		while (!IsNumberBetween(Number, from, to)) {
			cout << err ;
			Number = ReadIntNumber();
		}
		return Number;
	}
	
	static short ReadShortNumberBetween(short from, short to, string err = "Number is not within range, Enter again:\n") {
		short Number = ReadIntNumber();

		while (!IsNumberBetween(Number, from, to)) {
			cout << err;
			Number = ReadIntNumber();
		}
		return Number;

	}

	static double ReadDblNumber(string err = "Invalid Number, Enter again\n") {
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << err;
		}
		return Number;
	}
	static double ReadDblNumberBetween(double from, double to, string err  = "Number is not within range, Enter again:\n") {
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, from, to)) {
			cout << err;
			Number = ReadDblNumber();
		}
		return Number;
	}
	static bool IsValideDate(clsDate Date){
		clsDate::IsValidDate(Date);
	}
	
	static string ReadString() {

		string s = ""; 
		getline(cin >> ws, s);
		return s; 
	}

};

