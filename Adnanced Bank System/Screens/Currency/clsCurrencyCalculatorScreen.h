#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;
class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static float _readAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		float Amount = clsInputValidate<float>::ReadNumber();
		return Amount;
	}
	static clsCurrency _getCurrency(string Message)
	{
		cout << Message << endl;
		string CurrencyCode = clsInputValidate<string>::ReadString();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, Choose another one: ";
			CurrencyCode = clsInputValidate<string>::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}
	static void _printCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
	{
		cout << "\n" << Title << "\n";
		cout << "\n--------------------------\n";
		cout << "\nCountry      : " << Currency.GetCountry();
		cout << "\nCode         : " << Currency.GetCurrencyCode();
		cout << "\nName         : " << Currency.GetCurrencyName();
		cout << "\nRate(1$)     : " << Currency.GetRate();
		cout << "\n\n--------------------------\n\n";
	}
	static void _printCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		_printCurrencyCard(Currency1, "Convert From:");
		float AmountInUSD = Currency1.ConvertToUSD(Amount);
		cout << Amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInUSD << " USD\n";
		if (Currency2.GetCurrencyCode() == "USD") return;
		cout << "\nConverting from USD to:\n";
		_printCurrencyCard(Currency2, "To:");
		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);
		cout << Amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.GetCurrencyCode();
	}
public:
	static void ShowCurrencyCalculatorScreen()
	{
		char Answer = 'N';
		do
		{
			system("cls");
			_drawScreenHeader("\tUpdate Currency Screen");
			clsCurrency CurrencyFrom = _getCurrency("\nPlease Enter Currency1 Code: ");
			clsCurrency CurrencyTo = _getCurrency("\nPlease Enter Currency2 Code: ");
			float Amount = _readAmount();
			_printCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
			cout << "Do you want to perform another calculation? y/n? ";
			cin >> Answer;
		} while (toupper(Answer) == 'Y');
	}
};