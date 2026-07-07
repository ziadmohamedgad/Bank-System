#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include <iomanip>
using namespace std;
class clsScreen
{
protected:
    static void _drawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n";
        cout << "\n\t\t\t\t\tUser: " << CurrentUser.UserName << "\n";
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n";
    }
    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
    }
};
