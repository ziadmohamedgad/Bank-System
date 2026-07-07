#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrency.h"
class clsCurrienciesListScreen : protected clsScreen
{
private:
	static void _printCurrencyRecordLine(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.GetCountry();
		cout << "| " << setw(8) << left << Currency.GetCurrencyCode();
		cout << "| " << setw(45) << left << Currency.GetCurrencyName();
		cout << "| " << setw(10) << left << Currency.Rate;
	}
public:
	static void ShowListCurrenciesScreen()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Title = "\t  Currencies List Screen\n";
		string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currency.";
		_drawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t------------------------------------------------------------------------------------------------------\n";
		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << setw(8) << left << "Code";
		cout << "| " << setw(45) << left << "Name";
		cout << "| " << setw(10) << left << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t------------------------------------------------------------------------------------------------------\n\n";
		if (!vCurrencies.size())
		{
			cout << "\t\t\t\tNo Currencies Available In the System!\n";
		}
		else
			for (clsCurrency C : vCurrencies)
			{
				_printCurrencyRecordLine(C);
				cout << endl;
			}
		cout << setw(8) << left << "" << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
	}
};