#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _printCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n-----------------------------\n";
		cout << "\nCountry    : " << Currency.GetCountry();
		cout << "\nCode       : " << Currency.GetCurrencyCode();
		cout << "\nName       : " << Currency.GetCurrencyName();
		cout << "\nRate(1$) = : " << Currency.GetRate();
		cout << "\n-----------------------------\n";
	}
	static void _showResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\n\nCurrency Found :-)\n";
			_printCurrencyCard(Currency);
		}
		else
			cout << "\nCurrency Was Not Found :-(\n";
	}
public:
	static void ShowFindCurrencyScreen()
	{
		_drawScreenHeader("\t  Find Currency Screen");
		cout << "\n\nFind By: [1] Code or [2] Country? ";
		short Choice = clsInputValidate<short>::ReadRangedNumber(1, 2);
		switch (Choice)
		{
		case 1:
		{
			cout << "\n\nPlease Enter CurrencyCode: ";
			string CurrencyCode = clsInputValidate<string>::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_showResults(Currency);
			break;
		}
		case 2:
		{
			cout << "\n\nPlease Enter Country Name: ";
			string CountryName = clsInputValidate<string>::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(CountryName);
			_showResults(Currency);
			break;
		}
		}
	}
};