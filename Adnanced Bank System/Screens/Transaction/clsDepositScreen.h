#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
class clsDepositScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.PhoneNumber;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }
public:
    static void ShowDepositScreen()
    {
        _drawScreenHeader("\t  Deposit Screen");
        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsInputValidate<string>::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient With [" << AccountNumber << "] is not Exist, Enter Another one: ";
            AccountNumber = clsInputValidate<string>::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        cout << "\nPlease Enter Deposit Amount: ";
        float Amount = clsInputValidate<float>::ReadNumber();
        while (Amount <= 0)
        {
            cout << "\nPlease Insert A Valid Amount : ";
            Amount = clsInputValidate<float>::ReadNumber();
        }
        cout << "\nAre you sure you want to perform this transaction? y/n? ";
        char SureToDeposit = 'N';
        cin >> SureToDeposit;
        if (toupper(SureToDeposit) == 'Y')
        {
            Client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance is: " << Client.AccountBalance;
        }
        else
        {
            "\nOperation Was Cancelled.\n";
        }
    }
};

