#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.GetFullName();;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}
	static string _readAccountNumber(string Who = "")
	{
		cout << "\nPlease Enter Account Number to Transfer " << Who << ": ";
		string AccountNumber = clsInputValidate<string>::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not exist, Choose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}
		return AccountNumber;
	}
	static float ReadAmount(clsBankClient SourceClient)
	{
		cout << "\nEnter Transfer Amount? ";
		float Amount = clsInputValidate<float>::ReadNumber();
		while (Amount > SourceClient.AccountBalance || Amount <= 0)
		{
			cout << "\nNot allowed, the transaction exceeds your balance!, Insert Another Value: \n";
			Amount = clsInputValidate<float>::ReadNumber();
		}
		return Amount;
	}
public:
	static void ShowTransferScreen()
	{
		_drawScreenHeader("\tTransfer Screen");
		clsBankClient SourceClient = clsBankClient::Find(_readAccountNumber("From"));
		_PrintClient(SourceClient);
		clsBankClient DestinationClient = clsBankClient::Find(_readAccountNumber("To"));
		_PrintClient(DestinationClient);
		float Amount = ReadAmount(SourceClient);
		cout << "\nAre you sure you want to perform this operation? y/n? ";
		char SureToTransfer = '\0';
		cin >> SureToTransfer;
		if (toupper(SureToTransfer) == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "\nTransfer done successfully.\n";
			}
			else
			{
				cout << "\nTransfer failed.\n";
			}
		}
		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
	}
};