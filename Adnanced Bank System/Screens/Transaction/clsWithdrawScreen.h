#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsWithdrawScreen : protected clsScreen
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
    static void ShowWithdrawScreen()
    {
        _drawScreenHeader("\t  Withdraw Screen");
        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsInputValidate<string>::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Not Found, Enter Another One: ";
            AccountNumber = clsInputValidate<string>::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        cout << "\nPlease Enter Withdraw Amount: ";
        float Amount = clsInputValidate<float>::ReadNumber();
        while (Amount > Client.AccountBalance)
        {
            cout << "\nNot allowed, the transaction exceeds your balance !\n";
            cout << "Insert Another Value Up To : " << Client.AccountBalance << "\n";
            Amount = clsInputValidate<float>::ReadRangedNumber(1, Client.AccountBalance);
        }
        cout << "\nAre you sure you want to perform this transaction? y/n? ";
        char SureToWithdraw = 'N';
        cin >> SureToWithdraw;
        if (toupper(SureToWithdraw) == 'Y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdrawed Successfully.\n";
                cout << "\nNew Balance is: " << Client.AccountBalance;
            }
            else
            {
                cout << "\nCannot Withdraw Insufficient Balance!\n";
                cout << "\nAmount to Withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.AccountBalance;
            }
        }
        else
        {
            "\nOperation Was Cancelled.\n";
        }
    }
};

