#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
class clsDeleteUserScreen : protected clsScreen
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
	static void ShowDeleteUserScreen()
	{
		_drawScreenHeader("\tDelete User Screen");
		cout << "\nPlease Enter UserName: ";
		string UserName = clsInputValidate<string>::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser is no found, choose another one: ";
			UserName = clsInputValidate<string>::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		_printUserInfo(User);
		cout << "\nAre you sure you want to delete this User? y/n? ";
		char sureToDelete = 'N';
		cin >> sureToDelete;
		if (toupper(sureToDelete) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_printUserInfo(User);
			}
			else
			{
				cout << "\nError Uer Was not Deleted :-( , Try Again Later.\n";
			}
		}
	}
};