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
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;
    struct stTransferLogRecord;
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
        stClientRecord += Client.PhoneNumber + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);
        return stClientRecord;
    }
    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {
        vector <clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("Data/Clients.txt", ios::in);//read Mode
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
        MyFile.open("Data/Clients.txt", ios::out);//overwrite
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }
    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveCleintsDataToFile(_vClients);
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Data/Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName, string Separator = "#//#")
    {
        string _TransferRecord = "";
        _TransferRecord += clsDate::GetSystemDateTimeString() + Separator;
        _TransferRecord += AccountNumber() + Separator;
        _TransferRecord += DestinationClient.AccountNumber() + Separator;
        _TransferRecord += to_string(Amount) + Separator;
        _TransferRecord += to_string(AccountBalance) + Separator;
        _TransferRecord += to_string(DestinationClient.AccountBalance) + Separator;
        _TransferRecord += UserName;
        return _TransferRecord;
    }
    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {
        string dataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);
        fstream Myfile;
        Myfile.open("Data/TransferLog.txt", ios::out | ios::app);
        if (Myfile.is_open())
        {
            Myfile << dataLine << endl;
            Myfile.close();
        }
    }
    static stTransferLogRecord _convertTransferLogLineToRecord(string dataLine, string Separator = "#//#")
    {
        vector<string> TransferLogDataLine = clsString::Split(dataLine, Separator);
        stTransferLogRecord TransferLogRecord;
        TransferLogRecord.DateTime = TransferLogDataLine[0];
        TransferLogRecord.SourceAccountNum = TransferLogDataLine[1];
        TransferLogRecord.DestinationAccountNum = TransferLogDataLine[2];
        TransferLogRecord.Amount = stof(TransferLogDataLine[3]);
        TransferLogRecord.SourceBalanceAfter = stof(TransferLogDataLine[4]);
        TransferLogRecord.DestinationBalanceAfter = stof(TransferLogDataLine[5]);
        TransferLogRecord.UserName = TransferLogDataLine[6];
        return TransferLogRecord;
    }
public:
    struct stTransferLogRecord
    {
        string DateTime = "";
        string SourceAccountNum = "";
        string DestinationAccountNum = "";
        float Amount = 0;
        float SourceBalanceAfter = 0;
        float DestinationBalanceAfter = 0;
        string UserName = "";
    };
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
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
    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Data/Clients.txt", ios::in);

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
        MyFile.open("Data/Clients.txt", ios::in);
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
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }
        case enMode::AddNewMode:
        {
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
        }
    }
    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }
    bool Delete()
    {
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
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }
    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }
    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        double TotalBalances = 0;
        for (clsBankClient Client : vClients)
        {
            TotalBalances += Client.AccountBalance;
        }
        return TotalBalances;
    }
    bool Deposit(float Amount)
    {
        if (Amount <= 0) return false;
        _AccountBalance += Amount;
        Save();
        return true;
    }
    bool Withdraw(float Amount)
    {
        if (Amount > AccountBalance) return false;
        else 
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }
    bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
    {
        if (Amount > AccountBalance) return false;
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount,DestinationClient, UserName);
        return true;
    }
    static vector<stTransferLogRecord> GetTransfersLogList()
    {
        vector<stTransferLogRecord> vTransferLogRecord;
        fstream Myfile;
        Myfile.open("Data/TransferLog.txt", ios::in);
        if (Myfile.is_open())
        {
            string dataLine = "";
            while (getline(Myfile, dataLine))
            {
                vTransferLogRecord.push_back(_convertTransferLogLineToRecord(dataLine));
            }
            Myfile.close();
        }
        return vTransferLogRecord;
    }
};