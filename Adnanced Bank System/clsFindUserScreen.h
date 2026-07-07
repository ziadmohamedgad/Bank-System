#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;
class clsFindUserScreen : protected clsScreen
{
private:
	static void _printUserInfo(clsUser& User)
	{
		cout << "\nUser Card:\n";
		cout << "\n------------------------\n";
		cout << "\nFirstName    : " << User.FirstName;
		cout << "\nLastName     : " << User.LastName;
		cout << "\nFull Name    : " << User.GetFullName();
		cout << "\nEmail        : " << User.Email;
		cout << "\nPhone        : " << User.PhoneNumber;
		cout << "\nUser Name    : " << User.UserName;
		cout << "\nPassword     : " << User.Password;
		cout << "\nPermissions  : " << User.Permissions;
		cout << "\n------------------------\n";
	}
public:
	static void ShowFindUserScreen()
	{
		_drawScreenHeader("\t  Find User Screen");
		cout << "\nPlease Enter UserName: ";
		string Username = clsInputValidate<string>::ReadString();
		while (!clsUser::IsUserExist(Username))
		{
			cout << "\nUser is not found, choose another one: ";
			Username = clsInputValidate<string>::ReadString();
		}
		clsUser User = clsUser::Find(Username);
		if (!User.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}
		_printUserInfo(User);
	}
};