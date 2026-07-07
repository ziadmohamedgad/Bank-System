#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "ATMGlobal.h"
#include "clsATMMainScreen.h"
#include "clsInputValidate.h"

class clsATMLoginScreen : protected clsScreen
{
private:
    static bool _Login()
    {
        bool LoginFailed = false;
        string AccountNumber, PinCode;
        do
        {
            if (LoginFailed)
            {
                cout << "\nInvalid Account Number/PinCode!\n\n";
            }
            cout << "Enter Account Number? ";
            AccountNumber = clsInputValidate<string>::ReadString();
            cout << "Enter Pin? ";
            PinCode = clsInputValidate<string>::ReadString();

            CurrentClient = clsBankClient::Find(AccountNumber, PinCode);
            LoginFailed = CurrentClient.IsEmpty();

        } while (LoginFailed);

        clsATMMainScreen::ShowATMMainMenu();
        return true;
    }
public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  ATM Login Screen");
        return _Login();
    }
};
