#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsDeleteClientScreen : protected clsScreen
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
	static void ShowDeleteClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteclient)) return;
		_drawScreenHeader("\tDelete Client Screen");
		cout << "\nPlease Enter Account Number: ";
		string AccountNumber = clsInputValidate<string>::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Not Exist, Enter Another One: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        char SureToDelete = 'N';
        cout << "\nAre you sure you want to delete this client? y/n? ";
        cin >> SureToDelete;
        if (toupper(SureToDelete) == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "Error Client Was Not Deleted\n";
            }
        }
        else
        {
            cout << "\nOperation Cancelled!\n";
        }
	}
};