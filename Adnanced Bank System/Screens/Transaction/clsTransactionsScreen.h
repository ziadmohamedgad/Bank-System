#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalances.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include "clsScreen.h"
using namespace std;
class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionMenueChoices
	{
		eDeposit = 1, eWithdraw = 2, eShowTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eShowMainMenue = 6
	};
	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 - 6]? ";
		return clsInputValidate<short>::ReadRangedNumber(1, 6, "Number is not within the range, Enter again form [1 - 6]: ");
	}
	static void _GoBackToTransactionsMenueScreen()
	{
		cout << "\n\tPress any key to go back to Transactions Menue...\n";
		system("pause>nul");
		ShowTransactions();
	}
	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}
	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}
	static void _ShowMainMenueScreen()
	{
		// do nothing here, pressing any key will direct the user to the main menue
	}
	static void _performTransactionsMenueChoices(enTransactionMenueChoices Choice)
	{
		system("cls");
		switch (Choice)
		{
		case clsTransactionsScreen::eDeposit:
		{
			_ShowDepositScreen();
			_GoBackToTransactionsMenueScreen();
			break;
		}
		case clsTransactionsScreen::eWithdraw:
		{
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenueScreen();
			break;
		}
		case clsTransactionsScreen::eShowTotalBalances:
		{
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenueScreen();
			break;
		}
		case clsTransactionsScreen::eTransfer:
		{
			_ShowTransferScreen();
			_GoBackToTransactionsMenueScreen();
			break;
		}
		case clsTransactionsScreen::eTransferLog:
		{
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenueScreen();
			break;
		}
		case clsTransactionsScreen::eShowMainMenue:
		{
			_ShowMainMenueScreen();
			break;
		}
		}
	}
public:
	static void ShowTransactions()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pTransactions)) return;
		system("cls");
		_drawScreenHeader("\t  Transactions Screen");
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		_performTransactionsMenueChoices((enTransactionMenueChoices)_ReadTransactionsMenueOption());
	}
};

