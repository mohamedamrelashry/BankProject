#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2 };
    enMode _Mode;
   

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }
   
    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }
    void _Update() {

        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }
        _SaveCleintsDataToFile(_vClients);
            
    }
    void _AddNew() {
        _AddDataLineToFile( _ConverClientObjectToLine(*this));

    }
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    string _ConverUserObjectToLoginLine(clsBankClient ClientDestination ,int Amount , 
        string UserName ,string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += clsDate::GetSystemDateTimeString() + Seperator;
        stClientRecord += AccountNumber() + Seperator;
        stClientRecord += ClientDestination.AccountNumber() + Seperator;
        stClientRecord += to_string(Amount) + Seperator;
        stClientRecord += to_string(AccountBalance) + Seperator;
        stClientRecord += to_string(ClientDestination.AccountBalance) + Seperator;
        stClientRecord += UserName;
            

        return stClientRecord;

    }
    void _RegisterTransferLog(clsBankClient ClientDestination, int Amount,
        string UserName)
    {

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        string DataLine;

        if (MyFile.is_open())
        {
            DataLine = _ConverUserObjectToLoginLine(ClientDestination,Amount,UserName);
            MyFile << DataLine << endl;

        }

        MyFile.close();
    }
    struct stTransferLogin;
    static stTransferLogin _ConvertTransferLoginLineToRecord(string Line
        , string Seperator = "#//#") {
        

        stTransferLogin TransferLogin; 
        vector <string> vTransferLoginRecord = clsString::Split(Line, Seperator);
        TransferLogin.Date = vTransferLoginRecord[0];
        TransferLogin.sAccountNumber = vTransferLoginRecord[1];
        TransferLogin.dAccountNumber = vTransferLoginRecord[2]; 
        TransferLogin.Amount = stoi(vTransferLoginRecord[3]); 
        TransferLogin.sBalance = stoi(vTransferLoginRecord[4]);
        TransferLogin.dBalance = stoi(vTransferLoginRecord[5]);
        TransferLogin.UserName = (vTransferLoginRecord[6]);

        return TransferLogin; 
    }

public:
    struct stTransferLogin {
        string Date;
        string sAccountNumber;
        string dAccountNumber; 
        int Amount; 
        int sBalance; 
        int dBalance; 
        string UserName; 
    };
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

     void Deposit(double Amount) {
        _AccountBalance += Amount; 
        Save();

    }
     bool  Withdraw(double Amount) {
         if (Amount  > AccountBalance) {
             return false; 

      }
         else
         {
             _AccountBalance -= Amount;
             Save();
         }

     }


    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }


    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }
    enum enSaveResults{ svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists = 2};

    static clsBankClient GetAddNewClientObject(string AccountNumber){
        return clsBankClient(enMode::AddNewMode,"","","","", AccountNumber ,"",0 );
    }

    bool Delete() {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;
    }
    enSaveResults Save() {
        switch (_Mode)
        {
        case clsBankClient::EmptyMode:
            return clsBankClient::svFaildEmptyObject;
            break;
        case clsBankClient::UpdateMode:
            _Update();
            return clsBankClient::svSucceeded;
            break;
        case clsBankClient::AddNewMode: 
            if (clsBankClient::IsClientExist(_AccountNumber)) {
                return clsBankClient::svFaildAccountNumberExists;

            }
            else {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
                break; 
            }
        }

    }
    
    static vector <clsBankClient> GetClientList() {
        return _LoadClientsDataFromFile(); 
    }

    static float GetTotalBalances()
    {
        float TotalBalances = 0; 
        vector <clsBankClient> vClients;
        vClients = clsBankClient::GetClientList();
        for (clsBankClient Client  :vClients) {
            TotalBalances += Client.GetAccountBalance();
        }
        return TotalBalances;
    }
    bool Transfer(float Amount, clsBankClient& DestinationClient,string UserName)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
         DestinationClient.Deposit(Amount);
        _RegisterTransferLog(DestinationClient,Amount,UserName);
        return true;
    }
    static vector<stTransferLogin> GetTransferLoginList() {


        vector <stTransferLogin> vTransferLogin;
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read
        if (MyFile.is_open()) {

            string Line;

            stTransferLogin TransferLoginRecord;

            while (getline(MyFile, Line))
            {

                TransferLoginRecord = _ConvertTransferLoginLineToRecord(Line);

                 vTransferLogin.push_back(TransferLoginRecord);

            }

        }
        return vTransferLogin;
    }
};