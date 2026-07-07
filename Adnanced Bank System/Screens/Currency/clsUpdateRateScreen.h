#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;
class clsUpdateRateScreen : protected clsScreen
{
protected:
	static float _readRate()
	{
		cout << "\nEnter New Rate: ";
		float NewRate = clsInputValidate<float>::ReadNumber();
		return NewRate;
	}
	static void _printCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n-----------------------------\n";
		cout << "\nCountry    : " << Currency.GetCountry();
		cout << "\nCode       : " << Currency.GetCurrencyCode();
		cout << "\nName       : " << Currency.GetCurrencyName();
		cout << "\nRate(1$) = : " << Currency.GetRate();
		cout << "\n-----------------------------\n";
	}
public:
	static void ShowUpdateRateScreen()
	{
		_drawScreenHeader("\tUpdate Currency Screen");
		cout << "\n\nPlease Enter Currency Code: ";
		string CurrencyCode = clsInputValidate<string>::ReadString();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate<string>::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_printCurrency(Currency);
		cout << "\nAre you sure you want to update the rate of this Currency y/n? ";
		char SureToUpdate = 'N';
		cin >> SureToUpdate;
		if (toupper(SureToUpdate) == 'Y')
		{
			cout << "\n\nUpdate Currency Rate:";
			cout << "\n----------------------\n";
			Currency.UpdateRate(_readRate());
			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_printCurrency(Currency);
		}
	}
};