#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "ATMGlobal.h"
#include "clsATMCheckBalanceScreen.h"
#include "clsATMQuickWithdrawScreen.h"
#include "clsATMNormalWithdrawScreen.h"
#include "clsATMDepositScreen.h"

using namespace std;

class clsATMMainScreen : protected clsScreen
{
private:
    enum enATMMenuChoices
    {
        eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5
    };

    static short _ReadATMMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 - 5]? ";
        return clsInputValidate<short>::ReadRangedNumber(1, 5, "Number is not within the range, Enter again form [1 - 5]: ");
    }

    static void _GoBackToATMMenu()
    {
        cout << "\n\tPress any key to go back to ATM Menu...\n";
        system("pause>nul");
        ShowATMMainMenu();
    }

    static void _ShowQuickWithdrawScreen()
    {
        clsATMQuickWithdrawScreen::ShowQuickWithdrawScreen();
    }

    static void _ShowNormalWithdrawScreen()
    {
        clsATMNormalWithdrawScreen::ShowNormalWithdrawScreen();
    }

    static void _ShowDepositScreen()
    {
        clsATMDepositScreen::ShowDepositScreen();
    }

    static void _ShowCheckBalanceScreen()
    {
        clsATMCheckBalanceScreen::ShowCheckBalanceScreen();
    }

    static void _Logout()
    {
        CurrentClient = clsBankClient::Find("", "");
        // Returns to Login Screen loop
    }

    static void _PerformATMMenuChoices(enATMMenuChoices Choice)
    {
        switch (Choice)
        {
        case eQuickWithdraw:
            system("cls");
            _ShowQuickWithdrawScreen();
            _GoBackToATMMenu();
            break;
        case eNormalWithdraw:
            system("cls");
            _ShowNormalWithdrawScreen();
            _GoBackToATMMenu();
            break;
        case eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToATMMenu();
            break;
        case eCheckBalance:
            system("cls");
            _ShowCheckBalanceScreen();
            _GoBackToATMMenu();
            break;
        case eLogout:
            _Logout();
            break;
        }
    }

public:
    static void ShowATMMainMenu()
    {
        system("cls");
        _drawScreenHeader("\t\tATM Main Menu", "", CurrentClient.GetFullName());
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  ATM Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Quick Withdraw.\n";
        cout << setw(37) << left << "" << "\t[2] Normal Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Deposit.\n";
        cout << setw(37) << left << "" << "\t[4] Check Balance.\n";
        cout << setw(37) << left << "" << "\t[5] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformATMMenuChoices((enATMMenuChoices)_ReadATMMenuOption());
    }
};
