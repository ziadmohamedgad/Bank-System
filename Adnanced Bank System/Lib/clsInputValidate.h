#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;
template <typename T> class clsInputValidate
{
public:
	static bool IsNumberBetween(T Num, T From, T To)
	{
		return From <= Num && To >= Num;
	}
	static bool IsDateBetween(T Date, T From, T To)
	{
		if (T::IsDate1AfterDate2(From, To))
			T::SwapDates(From, To);
		switch (T::CompareDates(Date, From))
		{
		case T::enDateCompare::After:
		case T::enDateCompare::Equal:
		{
			switch (T::CompareDates(Date, To))
			{
			case T::enDateCompare::Before:
			case T::enDateCompare::Equal:
				return true;
			}
		}
		}
		return false;
	}
	static T ReadNumber(string InvalidMessage = "Invalid Number, Enter Again: ")
	{
		T Num = 0;
		cin >> Num;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << InvalidMessage;
			cin >> Num;
		}
		return Num;
	}
	static T ReadRangedNumber(T From, T To, string InvalidMessage = "Number is not within range, Enter Again: ")
	{
		T Num = 0;
		Num = ReadNumber();
		while (!IsNumberBetween(Num, From, To))
		{
			cout << InvalidMessage;
			Num = ReadNumber();
		}
		return Num;
	}
	static bool IsValidDate(T Date)
	{
		return T::IsValidDate(Date);
	}
	static T ReadString()
	{
		T S = "";
		getline(cin >> ws, S);
		return S;
	}
};