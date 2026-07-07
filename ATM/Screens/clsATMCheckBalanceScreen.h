#pragma once
#include <iostream>
#include "clsScreen.h"
#include "ATMGlobal.h"

class clsATMCheckBalanceScreen : protected clsScreen
{
public:
    static void ShowCheckBalanceScreen()
    {
        _DrawScreenHeader("\t   Check Balance Screen");
        cout << "\nYour Balance is  : " << CurrentClient.AccountBalance << "\n";
    }
};
