#pragma once
#include <iostream>
#include "clsString.h"
#include "clsPerson.h"
#include "vector"
#include "string"
#include "fstream"
#include "clsBankClient.h"
#include "clsUtility.h"
using namespace std;
class clsUser : public clsPerson
{
private:
	enum enMode
	{
		eEmptyMode = 0, eUpdateMode = 1, eAddNewMode = 2
	};
	enMode _Mode = enMode::eEmptyMode;
	string _UserName = "";
	string _Password = "";
	short _Permissions = 0;
	bool _markForDelete = false;
	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _convertLoginRegisterLineToRecord(string dataLine, string Separator = "#//#")
	{
		vector<string> LoginRegisterDataLine = clsString::Split(dataLine, Separator);
		stLoginRegisterRecord LoginRegisterRecord;
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtility::DecryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = static_cast<short>(stoi(LoginRegisterDataLine[3]));
		return LoginRegisterRecord;
	}
	static clsUser _convertDataLineToUserObject(string dataLine, string Separator = "#//#")
	{
		vector<string> vUser = clsString::Split(dataLine, Separator);
		return clsUser(enMode::eUpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], clsUtility::DecryptText(vUser[5]), static_cast<short>(stoi(vUser[6])));
	}
	static string _convertObjectToDataLine(clsUser U, string Separator = "#//#")
	{
		string dataLine = "";
		dataLine += U.FirstName + Separator;
		dataLine += U.LastName + Separator;
		dataLine += U.Email + Separator;
		dataLine += U.PhoneNumber + Separator;
		dataLine += U.UserName + Separator;
		dataLine += clsUtility::EncryptText(U.Password) + Separator;
		dataLine += to_string(U.Permissions);
		return dataLine;
	}
	static vector<clsUser> _loadUsersFormFile()
	{
		vector<clsUser> vUsers;
		fstream MyFile;
		MyFile.open("Data/Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string dataLine = "";
			while (getline(MyFile, dataLine))
			{
				vUsers.push_back(_convertDataLineToUserObject(dataLine));
			}
			MyFile.close();
		}
		return vUsers;
	}
	void _saveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Data/Users.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsUser& U : vUsers)
			{
				if (!U.MarkedForDelete())
				{
					MyFile << _convertObjectToDataLine(U) << endl;
				}
			}
			MyFile.close();
		}
	}
	void _Update()
	{
		vector<clsUser> _vUsers = _loadUsersFormFile();
		for (clsUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{
				U = *this;
				break;
			}
		}
		_saveUsersDataToFile(_vUsers);
	}
	void _AddNew()
	{
		_addDataLineToFile(_convertObjectToDataLine(*this));
	}
	void _addDataLineToFile(string dataLine)
	{
		fstream MyFile;
		MyFile.open("Data/Users.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << dataLine << endl;
			MyFile.close();
		}
	}
	static clsUser _getEmptyUserObject()
	{
		return clsUser(enMode::eEmptyMode, "", "", "", "", "", "", 0);
	}
	string _PrepareLogInRecord(string Separator = "#//#")
	{
		string _LoginRecord = "";
		_LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		_LoginRecord += UserName + Separator;
		_LoginRecord += clsUtility::EncryptText(Password) + Separator;
		_LoginRecord += to_string(Permissions);
		return _LoginRecord;
	}
public:
	enum enPermissions
	{
		eAll = -1, pListClients = 1, pAddNewclient = 2, pDeleteclient = 4, pUpdateClients = 8,
		pFindClient = 16, pTransactions = 32, pManageUsers = 64, pShowLoginRegister = 128, pCurrencyExchange = 256
	};
	struct stLoginRegisterRecord
	{
		string DateTime = "";
		string UserName = "";
		string Password = "";
		int Permissions = 0;
	};
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber, string UserName, string Password, short Permission) : clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permission;
	}
	bool IsEmpty()
	{
		return _Mode == enMode::eEmptyMode;
	}
	bool MarkedForDelete()
	{
		return _markForDelete;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;
	void SetPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}
	short GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;
	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Data/Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string dataLine = "";
			while (getline(MyFile, dataLine))
			{
				clsUser User = _convertDataLineToUserObject(dataLine);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _getEmptyUserObject();
	}
	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Data/Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string dataLine = "";
			while (getline(MyFile, dataLine))
			{
				clsUser User = _convertDataLineToUserObject(dataLine);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _getEmptyUserObject();
	}
	enum enSaveResults
	{
		svFailedEmptyObject = 0, svSucceeded = 1, svFailedUserExists = 2
	};
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsUser::eEmptyMode:
		{
			if (IsEmpty())
			return enSaveResults::svFailedEmptyObject;
		}
		case clsUser::eUpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}
		case clsUser::eAddNewMode:
		{
			if (IsUserExist(_UserName))
			{
				return enSaveResults::svFailedUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::eUpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
		}
	}
	static bool IsUserExist(string UserName)
	{
		return !Find(UserName).IsEmpty();
	}
	bool Delete()
	{
		vector<clsUser> vUsers = _loadUsersFormFile();
		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._markForDelete = true;
				break;
			}
		}
		_saveUsersDataToFile(vUsers);
		*this = _getEmptyUserObject();
		return true;
	}
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::eAddNewMode, "", "", "", "", UserName, "", 0);
	}
	static vector<clsUser> GetUsersList()
	{
		return _loadUsersFormFile();
	}
	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll) return true;
		else if ((Permission & this->Permissions) == Permission) return true;
		else return false;
	}
	void RegisterLogin()
	{
		string dataLine = _PrepareLogInRecord();
		fstream Myfile;
		Myfile.open("Data/LoginRegister.txt", ios::out | ios::app);
		if (Myfile.is_open())
		{
			Myfile << dataLine << endl;
			Myfile.close();
		}
	}
	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector<stLoginRegisterRecord> vLoginRegisterRecord;
		fstream Myfile;
		Myfile.open("Data/LoginRegister.txt", ios::in);
		if (Myfile.is_open())
		{
			string dataLine = "";
			while (getline(Myfile, dataLine))
			{
				vLoginRegisterRecord.push_back(_convertLoginRegisterLineToRecord(dataLine));
			}
			Myfile.close();
		}
		return vLoginRegisterRecord;
	}
};