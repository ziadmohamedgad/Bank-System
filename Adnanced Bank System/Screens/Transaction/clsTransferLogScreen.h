#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;
class clsTransferLogScreen : protected clsScreen
{
private:
    static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountNum;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNum;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.SourceBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.DestinationBalanceAfter;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;
    }
public:
	static void ShowTransferLogScreen()
	{
		vector<clsBankClient::stTransferLogRecord> vTransferLogRecords = clsBankClient::GetTransfersLogList();
		string Title = "\tTransfer Log List Screen";
		string SubTilte = "\t    (" + to_string(vTransferLogRecords.size()) + ") Record(s).";
		_drawScreenHeader(Title, SubTilte);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vTransferLogRecords.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else
            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecords)
            {
                PrintTransferLogRecordLine(Record);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};