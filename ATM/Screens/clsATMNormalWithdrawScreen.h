#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "ATMGlobal.h"

class clsATMNormalWithdrawScreen : protected clsScreen
{
public:
    static void ShowNormalWithdrawScreen()
    {
        _drawScreenHeader("\t  Normal Withdraw Screen", "", CurrentClient.FullName);
        
        int Amount = 0;
        do
        {
            cout << "\nEnter an amount multiple of 5's ? ";
            Amount = clsInputValidate<int>::ReadNumber();
        } while (Amount % 5 != 0);

        if (Amount > CurrentClient.AccountBalance)
        {
            cout << "\nThe amount exceeds your balance, make another choice.\n";
            return;
        }

        cout << "\nAre you sure you want perform this transaction? y/n ? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            CurrentClient.Withdraw(Amount);
            cout << "\nAmount Withdrawn Successfully.\n";
            cout << "\nNew Balance is: " << CurrentClient.AccountBalance;
        }
    }
};
