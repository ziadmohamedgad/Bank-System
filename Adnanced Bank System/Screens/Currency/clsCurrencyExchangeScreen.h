#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrienciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;
class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeMenue
	{
		cListCurrencies = 1, cFindCurrency = 2, cUpdateRate = 3, cCurrencyCalculator = 4, cMainMenue = 5
	};
	static short _readMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 - 5]? ";
		return clsInputValidate<short>::ReadRangedNumber(1, 5, "Number is not within the range, Enter again form [1 - 5]: ");
	}
	static void _goBackCurrencyExchangeMenue()
	{
		cout << "\nPress any key to go back to Currencies Menue...\n";
		system("pause>nul");
		ShowCurrencyExchangeScreen();
	}
	static void _showListCurrenciesScreen()
	{
		clsCurrienciesListScreen::ShowListCurrenciesScreen();
	}
	static void _showFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _showUpdateRateScreen()
	{
		clsUpdateRateScreen::ShowUpdateRateScreen();
	}
	static void _showCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}
	static void _performMainMenueChoices(enCurrencyExchangeMenue Choice)
	{
		system("cls");
		switch (Choice)
		{
		case clsCurrencyExchangeScreen::cListCurrencies:
		{
			_showListCurrenciesScreen();
			_goBackCurrencyExchangeMenue();
			break;
		}
		case clsCurrencyExchangeScreen::cFindCurrency:
		{
			_showFindCurrencyScreen();
			_goBackCurrencyExchangeMenue();
			break;
		}
		case clsCurrencyExchangeScreen::cUpdateRate:
		{
			_showUpdateRateScreen();
			_goBackCurrencyExchangeMenue();
			break;
		}
		case clsCurrencyExchangeScreen::cCurrencyCalculator:
		{
			_showCurrencyCalculatorScreen();
			_goBackCurrencyExchangeMenue();
			break;
		}
		case clsCurrencyExchangeScreen::cMainMenue:
		{
			break;
		}
		}
	}
public:
	static void ShowCurrencyExchangeScreen()
	{
		system("cls");
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pCurrencyExchange)) return;
		_drawScreenHeader("    Currency Exchange Main Screen");
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		_performMainMenueChoices((enCurrencyExchangeMenue)_readMainMenueOption());
	}
};