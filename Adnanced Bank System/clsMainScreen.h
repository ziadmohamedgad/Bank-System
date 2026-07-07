#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsAddNewClientMenue.h"
#include "clsClientsListScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"
#include "clsScreen.h"
#include "Global.h"
using namespace std;
class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenueChoices
	{
		eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClientInfo = 4, 
		eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLoginRegister = 8,
		eCurrencyExchange = 9, eExit = 10
	};
	static short _readMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 - 10]? ";
		return clsInputValidate<short>::ReadRangedNumber(1, 10, "Number is not within the range, Enter again form [1 - 10]: ");
	}
	static void _goBackToMainMenue()
	{
		cout << "\n\tPress any key to go back to Main Menue...\n";
		system("pause > 0");
		showMainMenue();
	}
	static void _showClientsListScreen()
	{
		clsClientsListScreen::ShowClientsList();
	}
	static void _showAddNewClientScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}
	static void _showDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _showUpdateClientInfoScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _showFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}
	static void _showTransactionsScreen()
	{
		clsTransactionsScreen::ShowTransactions();
	}
	static void _showManageUsersScreen()
	{
		clsManageUsersMenue::ShowManageUsersMenue();
	}
	static void _showLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	static void _showCurrencyExchangeScreen()
	{
		clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
	}
	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}
	static void _performMainMenueChoices(enMainMenueChoices Choice)
	{
		system("cls");
		switch (Choice)
		{
		case clsMainScreen::eShowClientList:
		{
			_showClientsListScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eAddNewClient:
		{
			_showAddNewClientScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eDeleteClient:
		{
			_showDeleteClientScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eUpdateClientInfo:
		{
			_showUpdateClientInfoScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eFindClient:
		{
			_showFindClientScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eTransactions:
		{
			_showTransactionsScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eManageUsers:
		{
			_showManageUsersScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eLoginRegister:
		{
			_showLoginRegisterScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eCurrencyExchange:
		{
			_showCurrencyExchangeScreen();
			_goBackToMainMenue();
			break;
		}
		case clsMainScreen::eExit:
		{
			_Logout();
			break;
		}
		}
	}
public:
	static void showMainMenue()
	{
		system("cls");
		_drawScreenHeader("\t\tMain Screen");
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		_performMainMenueChoices((enMainMenueChoices)_readMainMenueOption());
	}
};