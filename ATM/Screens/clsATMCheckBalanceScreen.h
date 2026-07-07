#pragma once
#include <iostream>
#include "clsScreen.h"
#include "ATMGlobal.h"

class clsATMCheckBalanceScreen : protected clsScreen
{
public:
    static void ShowCheckBalanceScreen()
    {
        _drawScreenHeader("\t   Check Balance Screen", "", CurrentClient.FullName);
        cout << "\nYour Balance is  : " << CurrentClient.AccountBalance << "\n";
    }
};
