#pragma once
#include <iostream>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFailed = false;
		string UserName, Password;
		short FailedLoginCount = 0;
		do
		{
			if (LoginFailed)
			{
				FailedLoginCount++;
				cout << "\nInvalid Username/Password!";
				cout << "\nYou have " << 3 - FailedLoginCount << " Trial(s) to login.\n\n";
				if (FailedLoginCount == 3)
				{
					cout << "\nYou are Locked after 3 failed trails\n\n";
					return false;
				}
			}
			cout << "Enter UserName? ";
			UserName = clsInputValidate<string>::ReadString();
			cout << "Enter Password? ";
			Password = clsInputValidate<string>::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();
		} while (LoginFailed);
		CurrentUser.RegisterLogin();
		clsMainScreen::showMainMenue();
	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_drawScreenHeader("\t  Login Screen");
		return _Login();
	}
};