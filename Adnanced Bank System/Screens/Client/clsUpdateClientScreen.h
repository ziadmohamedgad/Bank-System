#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;
class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate<string>::ReadString();
        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate<string>::ReadString();
        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate<string>::ReadString();
        cout << "\nEnter Phone: ";
        Client.PhoneNumber = clsInputValidate<string>::ReadString();
        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate<string>::ReadString();
        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate<float>::ReadNumber();
    }
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.PhoneNumber;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }
public:
	static void ShowUpdateClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) return;
		_drawScreenHeader("\tUpdate Client Screen");
		cout << "\nPlease Enter Account Number: ";
		string AccountNumber = clsInputValidate<string>::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is Not Exist, Enter Another One: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        cout << "\nAre you sure you want to update this client? y/n? ";
        char SureToUpdate = 'N';
        cin >> SureToUpdate;
        if (toupper(SureToUpdate) == 'Y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";
            _ReadClientInfo(Client);
            clsBankClient::enSaveResults SaveResult = Client.Save();
            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClient(Client);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            }
        }
    }
};