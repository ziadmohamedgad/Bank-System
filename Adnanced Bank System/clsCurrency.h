#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;
class clsCurrency
{
private:
	enum enMode
	{
		EmptyMode = 0, UpdateMode = 1
	};
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;
	static clsCurrency _ConvertLineToCurrecyObject(string dataLine, string Separator = "#//#")
	{
		vector<string> vCurrency = clsString::Split(dataLine, Separator);
		return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
	}
	static string _ConvertCurrecyObjectToLine(clsCurrency Currency, string Separator = "#//#")
	{
		string _dataLine = "";
		_dataLine += Currency.GetCountry() + Separator;
		_dataLine += Currency.GetCurrencyCode() + Separator;
		_dataLine += Currency.GetCurrencyName() + Separator;
		_dataLine += Currency.GetRate();
		return _dataLine;
	}
	static vector<clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector<clsCurrency> _vCurrencies;
		fstream _Myfile;
		_Myfile.open("Currencies.txt", ios::in);
		if (_Myfile.is_open())
		{
			string _dataLine = "";
			while (getline(_Myfile, _dataLine))
			{
				_vCurrencies.push_back(_ConvertLineToCurrecyObject(_dataLine));
			}
			_Myfile.close();
		}
		return _vCurrencies;
	}
	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencies)
	{
		fstream _Myfile;
		_Myfile.open("Currencies.txt", ios::out);
		if (_Myfile.is_open())
		{
			for (clsCurrency C : vCurrencies)
			{
				_Myfile << _ConvertCurrecyObjectToLine(C) << endl;
			}
			_Myfile.close();
		}
	}
	void _Update()
	{

	}
	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}
public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	static vector<clsCurrency> GetAllUSDRates()
	{

	}
	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}
	string GetCountry()
	{
		return _Country;
	}
	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}
	string GetCurrencyName()
	{
		return _CurrencyName;
	}
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}
	float GetRate()
	{
		return _Rate;
	}
	__declspec(property(get = GetRate, put = UpdateRate)) float Rate;
	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream Myfile;
		Myfile.open("Currencies.txt", ios::in);
		if (Myfile.is_open())
		{
			string dataLine = "";
			while (getline(Myfile, dataLine))
			{
				clsCurrency Currency = _ConvertLineToCurrecyObject(dataLine);
				if (clsString::UpperAllString(Currency.GetCurrencyCode()) == CurrencyCode)
				{
					Myfile.close();
					return Currency;
				}
			}
			Myfile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);
		fstream Myfile;
		Myfile.open("Currencies.txt", ios::in);
		if (Myfile.is_open())
		{
			string dataLine = "";
			while (getline(Myfile, dataLine))
			{
				clsCurrency Currency = _ConvertLineToCurrecyObject(dataLine);
				if (clsString::UpperAllString(Currency.GetCountry()) == Country)
				{
					Myfile.close();
					return Currency;
				}
			}
			Myfile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	static bool IsCurrencyExist(string CurrencyCode)
	{
		return !FindByCode(CurrencyCode).IsEmpty();
	}
	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}
	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate);
	}
	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.GetCurrencyCode() == "USD") return AmountInUSD;
		return (float)(AmountInUSD * Currency2.Rate);
	}
};