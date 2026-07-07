#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "clsDate.h"
using namespace std;
class clsUtility
{
public:
	enum enCharType
	{
		eCapitalLetter = 1, eSmallLetter = 2, eDigit = 3, eSpecialChar = 4, eMix = 5
	};
	static void Srand()
	{
		srand((unsigned)time(NULL));
	}
	static int GetRandomNumber(int From, int To)
	{
		return rand() % (To - From + 1) + From;
	}
	static char GetRandomCharacter(enCharType CharType)
	{
		switch (CharType)
		{
		case clsUtility::eCapitalLetter:
			return char(GetRandomNumber(65, 90));
		case clsUtility::eSmallLetter:
			return char(GetRandomNumber(97, 122));
		case clsUtility::eDigit:
			return char(GetRandomNumber(48, 57));
		case clsUtility::eSpecialChar:
			return char(GetRandomNumber(33, 47));
		case clsUtility::eMix:
			return GetRandomCharacter(enCharType(GetRandomNumber(1, 4)));
		}
	}
	static string GenerateWord(enCharType CharType, short WordLength)
	{
		string Word = "";
		for (short i = 0; i < WordLength; i++)
		{
			Word += GetRandomCharacter(CharType);
		}
		return Word;
	}
	static string GenerateKey(enCharType CharType, short Slots, short SlotLength)
	{
		string Key = "";
		for (short i = 0; i < Slots; i++)
		{
			Key += GenerateWord(CharType, SlotLength);
			if (i != Slots - 1)
			{
				Key += '-';
			}
		}
		return Key;
	}
	static void GenerateKeys(enCharType CharType, short NumberOfKeys, short KeySlots, short KeySlotLength)
	{
		string Key = "";
		for (short i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Key [" << i << "] : ";
			cout <<	GenerateKey(CharType, KeySlots, KeySlotLength) << endl;
		}
	}
	static void Swap(int &Num1, int &Num2)
	{
		int Temp = 0;
		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}
	static void Swap(double &Num1, double &Num2)
	{
		double Temp = 0.0;
		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}
	static void Swap(string &S1, string &S2)
	{
		string Temp = "";
		Temp = S1;
		S1 = S2;
		S2 = Temp;
	}
	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate::SwapDates(Date1, Date2);
	}
	static void ShuffleArray(int Arr[], int arrLength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			Swap(Arr[GetRandomNumber(0, arrLength - 1)], Arr[GetRandomNumber(0, arrLength - 1)]);
		}
	}
	static void ShuffleArray(string Arr[], int arrLength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			Swap(Arr[GetRandomNumber(0, arrLength - 1)], Arr[GetRandomNumber(0, arrLength - 1)]);
		}
	}
	static void FillArrayWithRandomNumbers(int Arr[], int arrLength, int From, int To)
	{
		for (short i = 0; i < arrLength; i++)
		{
			Arr[i] = GetRandomNumber(From, To);
		}
	}
	static void FillArrayWithRandomWords(string Arr[], int arrLength, enCharType CharType, short EachWordLength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			Arr[i] = GenerateWord(CharType, EachWordLength);
		}
	}
	static void FillArrayWithRandomKeys(string Arr[], int arrLength, enCharType CharType, short EachKeySlots, short EachSlotLength)
	{
		for (short i = 0; i < arrLength; i++)
		{
			Arr[i] = GenerateKey(CharType, EachKeySlots, EachSlotLength);
		}
	}
	static string Tabs(short NumberOfTabs)
	{
		string t = "";
		for (short i = 0; i < NumberOfTabs; i++)
		{
			t += "\t ";
		}
		return t;
	}
	static string EncryptText(string Text, short EncryptionKey = 2)
	{
		for (short i = 0; i < Text.size(); i++)
		{
			Text[i] = Text[i] + EncryptionKey;
		}
		return Text;
	}
	static string DecryptText(string EncryptedText, short EncryptionKey = 2)
	{
		for (short i = 0; i < EncryptedText.size(); i++)
		{
			EncryptedText[i] = EncryptedText[i] - EncryptionKey;
		}
		return EncryptedText;
	}
	static string NumberToText(int Num)
	{
		if (!Num) return "";
		if (Num >= 1 && Num <= 19)
		{
			string Txt[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Tweleve",
			"Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen","Nineteen"};
			return Txt[Num] + " ";
		}
		else if (Num >= 20 && Num <= 99)
		{
			string Txt[] = { "", "", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eigthy", "Ninety" };
			return Txt[Num / 10] + " " + NumberToText(Num % 10);
		}
		else if (Num >= 100 && Num <= 999)
		{
			return NumberToText(Num / 100) + "Hundred " + NumberToText(Num % 100);
		}
		else if (Num >= 1000 && Num <= 999999)
		{
			return NumberToText(Num / 1000) + "Thousand " + NumberToText(Num % 1000);
		}
		else if (Num >= 1000000 && Num <= 999999999)
		{
			return NumberToText(Num / 1000000) + "Million " + NumberToText(Num % 1000000);
		}
		else
		{
			return NumberToText(Num / 1000000000) + "Billion " + NumberToText(Num % 1000000000);
		}
	}
};