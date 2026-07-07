#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;
class clsManageUsersMenue : protected clsScreen
{
private:
	enum enManageUsersChoices
	{
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
	};
	static short _readManageUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		return clsInputValidate<short>::ReadRangedNumber(1, 6);
	}
	static void _goBackToManageUsersMenue()
	{
		cout << "\n\tPress any key to go back to Manage Users Menue...\n";
		system("pause>nul");
		ShowManageUsersMenue();
	}
	static void _showListUsersScreen()
	{
		clsListUsersScreen::ShowListUsersScreen();
	}
	static void _showAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	static void _showDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _showUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _showFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}
	static void _performManageUsersChoices(enManageUsersChoices Choice)
	{
		system("cls");
		switch (Choice)
		{
		case clsManageUsersMenue::eListUsers:
		{
			_showListUsersScreen();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::eAddNewUser:
		{
			_showAddNewUserScreen();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::eDeleteUser:
		{
			_showDeleteUserScreen();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::eUpdateUser:
		{
			_showUpdateUserScreen();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::eFindUser:
		{
			_showFindUserScreen();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::eMainMenue:
			break;
		}
	}
public:
	static void ShowManageUsersMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers)) return;
		system("cls");
		_drawScreenHeader("\t Manage Users Screen");
		cout << setw(37) << left << "" << "============================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
		cout << setw(37) << left << "" << "============================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "============================================\n";
		_performManageUsersChoices(enManageUsersChoices(_readManageUsersMenueOption()));
	}
};