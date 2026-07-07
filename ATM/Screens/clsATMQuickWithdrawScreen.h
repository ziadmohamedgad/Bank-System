#pragma once
#include <iostream>
#include "clsScreen.h"
#include "ATMGlobal.h"

class clsATMQuickWithdrawScreen : protected clsScreen
{
private:
    static short _GetQuickWithdrawAmount(short Option)
    {
        switch (Option)
        {
        case 1: return 20;
        case 2: return 50;
        case 3: return 100;
        case 4: return 200;
        case 5: return 400;
        case 6: return 600;
        case 7: return 800;
        case 8: return 1000;
        default: return 0;
        }
    }

    static void _PerformQuickWithdraw(short Option)
    {
        if (Option == 9)
            return;

        short Amount = _GetQuickWithdrawAmount(Option);
        
        if (Amount > CurrentClient.AccountBalance)
        {
            cout << "\nThe amount exceeds your balance, make another choice.\n";
            cout << "Press Any key to continue...";
            system("pause>0");
            ShowQuickWithdrawScreen();
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

public:
    static void ShowQuickWithdrawScreen()
    {
        system("cls");
        _drawScreenHeader("\t  Quick Withdraw Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tQuick Withdraw Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] 20\t\t[2] 50\n";
        cout << setw(37) << left << "" << "\t[3] 100\t\t[4] 200\n";
        cout << setw(37) << left << "" << "\t[5] 400\t\t[6] 600\n";
        cout << setw(37) << left << "" << "\t[7] 800\t\t[8] 1000\n";
        cout << setw(37) << left << "" << "\t[9] Exit\n";
        cout << setw(37) << left << "" << "===========================================\n";

        cout << setw(37) << left << "" << "Your Balance is " << CurrentClient.AccountBalance << "\n";
        cout << setw(37) << left << "" << "Choose what to withdraw from [1] to [9] ? ";
        
        short Option = clsInputValidate<short>::ReadRangedNumber(1, 9, "Number is not within the range, Enter again form [1 - 9]: ");
        _PerformQuickWithdraw(Option);
    }
};
