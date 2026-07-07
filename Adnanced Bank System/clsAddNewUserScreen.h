#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;
class clsAddNewUserScreen : protected clsScreen
{
private:
	static short _readPermissionsToSet()
	{
		char _Choice = '\n';
		cout << "\nDo you want to give full access? y/n? ";
		cin >> _Choice;
		if (toupper(_Choice) == 'Y') return -1;
		else
		{
			short _Permissions = 0;
			cout << "\nDo you want to give access to : \n";
			cout << "\nShow Client List? y/n? ";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pListClients;
			cout << "\nAdd New Client? y/n?	";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pAddNewclient;
			cout << "\nDelete Client? y/n? ";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pDeleteclient;
			cout << "\nUpdate Client? y/n? ";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pUpdateClients;
			cout << "\nFind Client? y/n? ";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pFindClient;
			cout << "\nTransactions? y/n? ";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pTransactions;
			cout << "\nManage Users? y/n? ";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pManageUsers;
			cout << "\nShow Login Register? y/n? ";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pShowLoginRegister;
			cout << "\nCurrency Exchange? y/n? ";
			cin >> _Choice;
			if (toupper(_Choice) == 'Y') _Permissions += clsUser::enPermissions::pCurrencyExchange;
			return _Permissions;
		}
	}
	static void _readUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate<string>::ReadString();
		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate<string>::ReadString();
		cout << "\nEnter Email: ";
		User.Email = clsInputValidate<string>::ReadString();
		cout << "\nEnter Phone: ";
		User.PhoneNumber = clsInputValidate<string>::ReadString();
		cout << "\nEnter Password: ";
		User.Password = clsInputValidate<string>::ReadString();
		cout << "\nEnter Permission: ";
		User.Permissions = _readPermissionsToSet();
	}
	static void _printUserInfo(clsUser & User)
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
	static void ShowAddNewUserScreen()
	{
		_drawScreenHeader("\t  Add New User Screen");
		cout << "\nPlease Enter UserName : ";
		string UserName = clsInputValidate<string>::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name is Already Exist, Choose another one: ";
			UserName = clsInputValidate<string>::ReadString();
		}
		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
		_readUserInfo(NewUser);
		clsUser::enSaveResults Save = NewUser.Save();
		switch (Save)
		{
		case clsUser::svSucceeded:
		{
			cout << "\nUser Added Successfully :-)\n";
			_printUserInfo(NewUser);
			break;
		}
		case clsUser::svFailedEmptyObject:
		{
			cout << "\nError User was not saved because it's Empty";
			break;
		}
		case clsUser::svFailedUserExists:
		{
			cout << "\nError User was not saved because UserName is userd!\n";
			break;
		}
		}
	}
};