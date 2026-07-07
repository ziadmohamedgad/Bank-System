#pragma once
#include "iostream"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsFindClientScreen : protected clsScreen
{
private:
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
	static void ShowFindClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) return;
		_drawScreenHeader("\tFind Client Screen");
        cout << "\nPlease Enter Account Number: ";
		string AccountNumber = clsInputValidate<string>::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Not Exist, Enter Another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
        if (!Client.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient was not found :-(\n";
        }
        _PrintClient(Client);
	}
};