#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "ATMGlobal.h"

class clsATMDepositScreen : protected clsScreen
{
public:
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");
        
        cout << "\nEnter a positive Deposit Amount? ";
        double Amount = clsInputValidate<double>::ReadNumber();
        while (Amount <= 0)
        {
            cout << "\nInvalid Amount! Enter a positive Deposit Amount? ";
            Amount = clsInputValidate<double>::ReadNumber();
        }

        cout << "\nAre you sure you want perform this transaction? y/n ? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            CurrentClient.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance is: " << CurrentClient.AccountBalance;
        }
    }
};
