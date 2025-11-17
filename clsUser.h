#pragma once
#include "clsPerson.h"
#include <vector>
#include "clsString.h"
#include <fstream>

class clsUser  : public clsPerson
{

	private: 
       
		enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
		enMode _Mode;
		string _UserName, _Password; 
		int _Permissions; 
		bool _MarkedForDelete = 0; 

      
        struct stLoginRegisterRecord;
        static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
        {
            stLoginRegisterRecord LoginRegisterRecord;


            vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
            LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
            LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
            LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
            LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

            return LoginRegisterRecord;

        }
        static  vector <stLoginRegisterRecord> _LoadLoginDataFromFile()
        {

            vector <stLoginRegisterRecord> LoginRegisterRecord;

            fstream MyFile;
            MyFile.open("LoginRegister.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {

                string Line;


                while (getline(MyFile, Line))
                {

                    stLoginRegisterRecord Record 
                        = _ConvertLoginRegisterLineToRecord(Line);
                    
                    LoginRegisterRecord.push_back(Record);
                }

                MyFile.close();

            }

            return LoginRegisterRecord;

        }
        static clsUser _ConvertLinetoUserobject(string Line, string Seperator = "#//#")
        {
            vector<string> vClientData;
            vClientData = clsString::Split(Line, Seperator);

            return clsUser(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                vClientData[3], vClientData[4], clsUtil::DecryptText( vClientData[5]),stod(vClientData[6]));

        }

        static string _ConverUserObjectToLine(clsUser Client, string Seperator = "#//#")
        {
            
            string stClientRecord = "";
            stClientRecord += Client.FirstName + Seperator;
            stClientRecord += Client.LastName + Seperator;
            stClientRecord += Client.Email + Seperator;
            stClientRecord += Client.Phone + Seperator;
            stClientRecord += Client._UserName + Seperator;
            stClientRecord += clsUtil::EncryptText(Client._Password) + Seperator;
            stClientRecord += to_string(Client._Permissions);

            return stClientRecord;

        }

        static clsUser _GetEmptyClientObject()
        {
            return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
        }
        static  vector <clsUser> _LoadUsersDataFromFile()
        {

            vector <clsUser> vUsers;

            fstream MyFile;
            MyFile.open("Users.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {

                string Line;


                while (getline(MyFile, Line))
                {

                    clsUser Client = _ConvertLinetoUserobject(Line);

                    vUsers.push_back(Client);
                }

                MyFile.close();

            }

            return vUsers;

        }

        static void _SaveUsersDataToFile(vector <clsUser> vUsers)
        {

            fstream MyFile;
            MyFile.open("Users.txt", ios::out);//overwrite

            string DataLine;

            if (MyFile.is_open())
            {

                for (clsUser C : vUsers)
                {
                    if (C.MarkedForDeleted() == false)
                    {
                        //we only write records that are not marked for delete.  
                        DataLine = _ConverUserObjectToLine(C);
                        MyFile << DataLine << endl;

                    }

                }

                MyFile.close();

            }

        }
        void _Update() {

            vector <clsUser> _vUsers;
            _vUsers = _LoadUsersDataFromFile();

            for (clsUser& C : _vUsers) {
                if (C.UserName == UserName)
                {
                    C = *this;
                    break;
                }

            }
            _SaveUsersDataToFile(_vUsers);

        }
        void _AddNew() {
            _AddDataLineToFile(_ConverUserObjectToLine(*this));

        }
        void _AddDataLineToFile(string  stDataLine)
        {
            fstream MyFile;
            MyFile.open("Users.txt", ios::out | ios::app);

            if (MyFile.is_open())
            {

                MyFile << stDataLine << endl;

                MyFile.close();
            }

        }
         string _ConverUserObjectToLoginLine( string Seperator = "#//#")
        {
             
            string stClientRecord = "";
            stClientRecord += clsDate::GetSystemDateTimeString() + Seperator;
            stClientRecord += UserName + Seperator;
            stClientRecord += clsUtil::EncryptText(Password) + Seperator;
            stClientRecord += to_string(Permissions);

            return stClientRecord;

        }
         void _SaveCurrentUsersDataToLoginFile()
        {

            fstream MyFile;
            MyFile.open("LoginRegister.txt", ios::out | ios::app); 

            string DataLine;

            if (MyFile.is_open())
            {
                        DataLine = _ConverUserObjectToLoginLine();
                        MyFile << DataLine << endl;


             }

                MyFile.close();


        }

public: 
    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;

    };
    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;



    static clsUser Find(string UserName)
    {


        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser Client = _ConvertLinetoUserobject(Line);
                if (Client.UserName == UserName)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsUser Find(string UserName, string Password)
    {



        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser Client = _ConvertLinetoUserobject(Line);
                if (Client.UserName == UserName && Client.Password == Password)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }


    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    static clsUser GetAddNewUserObject(string UserName) {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    bool Delete() {
        vector <clsUser> _vClients;
        _vClients = _LoadUsersDataFromFile();

        for (clsUser& C : _vClients)
        {
            if (C.UserName == _UserName)
            {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;
    }
    enSaveResults Save() {
        switch (_Mode)
        {
        case clsUser::EmptyMode:
            return clsUser::svFaildEmptyObject;
            break;
        case clsUser::UpdateMode:
            _Update();
            return clsUser::svSucceeded;
            break;
        case clsUser::AddNewMode:
            if (clsUser::IsUserExist(_UserName)) {
                return clsUser::svFaildUserExists;

            }
            else {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
                break;
            }
        }
        
    }

    static vector <clsUser> GetUsersList() {
        return _LoadUsersDataFromFile();
    }

    static float GetTotalBalances()
    {
        float TotalBalances = 0;
        vector <clsUser> vUsers;
        vUsers = clsUser::GetUsersList();
        for (clsUser Client : vUsers) {
            TotalBalances += Client.GetTotalBalances();
        }
        return TotalBalances;
    }
    enum enPermissions {
      eAll = -1, pListCleints = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClient = 8, pFindClient = 16 , pTranactions = 32, pManageUsers = 64,
        pLoginList  =128 
    };
    bool CheckAccessPermission(enPermissions Permission) {
       
        if (this->Permissions == Permission)
            return true;
        if (this->Permissions & Permission == Permission)
            return true; 
        else {
            return false;
        }
    }   
     void RegisterLogIn() {

        _SaveCurrentUsersDataToLoginFile();
    }
     static vector<stLoginRegisterRecord> GetLoginRegisterList() {


         vector <stLoginRegisterRecord> vLoginRegisterRecord;
         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::in);
         if (MyFile.is_open()) {

             string Line;

             stLoginRegisterRecord LoginRegisterRecord;

             while (getline(MyFile, Line))
             {

                 LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

                 vLoginRegisterRecord.push_back(LoginRegisterRecord);

             }

         }
         return vLoginRegisterRecord; 
    }

};

