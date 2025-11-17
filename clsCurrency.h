#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"
#include <fstream>
class clsCurrency
{
	enum enMode {EmptyMode =  0 , UpdateMode = 1};
    enMode _Mode;
    string _Country; 
	string _CurrencyCode; 
	string _CurrencyName;
	float _Rate;
    static clsCurrency _GetEmptyCurrencyObject() {
       
        return clsCurrency(EmptyMode ,"","","",0);
    }
    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#") {
        vector <string> Currency = 
            clsString::Split(Line , Seperator);
        return clsCurrency(enMode::UpdateMode,Currency[0],
            Currency[1], Currency[2],  stod(Currency[3]));
    }
    static vector <clsCurrency> _LoadCurrencysDataFromFile() {

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode
        vector<clsCurrency> vCurrency;
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                
                vCurrency.push_back(Currency);
            }

            MyFile.close();

        }
        return vCurrency; 
    }
    static string _ConvertCurrencyObjectToDataLine(clsCurrency Currency, string Seperator = "#//#") {
        string stCurrencyRecord = "";
        stCurrencyRecord += Currency.Country() + Seperator;
        stCurrencyRecord += Currency.CurrencyCode() + Seperator;
        stCurrencyRecord += Currency.CurrencyName() + Seperator;
        stCurrencyRecord += to_string(Currency.Rate());

        return stCurrencyRecord;
        
    }
    static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrency) {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);//OverWrite Mode
        if (MyFile.is_open())
        {
            string DataLine;
            for (clsCurrency C:vCurrency) {
               
                DataLine = _ConvertCurrencyObjectToDataLine(C); 
                MyFile << DataLine << endl;
           }

            MyFile.close();

        }
    }
    void _Update() {
        vector <clsCurrency> _vCurrencys;
        _vCurrencys = _LoadCurrencysDataFromFile();

        for (clsCurrency& C : _vCurrencys)
        {
            if (C.CurrencyCode() == CurrencyCode())
            {
                C = *this;
                break;
            }

        }

        _SaveCurrencyDataToFile(_vCurrencys);

    }
public: 
    clsCurrency(enMode Mode,string Country , string CurrencyCode , string CurrencyName , float Rate) {
        _Mode = Mode; 
        _Country = Country;
        _CurrencyCode = CurrencyCode; 
        _CurrencyName = CurrencyName; 
        _Rate = Rate;
    }
    string Country()
    {
        return _Country;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    string CurrencyName()
    {
        return _CurrencyName;
    }
    void UpdateRate(float NewRate) {

        _Rate = NewRate;
        _Update();
     }
    float Rate() {
        return _Rate; 
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);


        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.Country() == Country)
                {
                    MyFile.close();
                    return Currency;
                }

            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();
    }
    static clsCurrency FindByCurrencyCode(string CurrencyCode)
    {

        CurrencyCode = clsString::UpperAllString(CurrencyCode);
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }

            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();
    }
     bool IsEmpty() {
        return _Mode == enMode::EmptyMode;
    }
    static bool IsCurrencyExist(string CurrencyCode) {
        clsCurrency C1 = FindByCurrencyCode(CurrencyCode);
        return (!C1.IsEmpty());
    }
    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencysDataFromFile();
    }

    float ConvertToUSD(float Amount){

        return (float)(Amount / Rate());


    }
    float ConvertToOtherCurrency(float Amount , clsCurrency Currency2 ) {

        if (Currency2.CurrencyCode() == "USD") {
            return float((ConvertToUSD(Amount)));

        }


        return (float)(ConvertToUSD(Amount) * Currency2.Rate());
    }



};

