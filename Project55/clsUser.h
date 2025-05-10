#pragma once

#include "clsPerson.h"
#include "clsString.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>
#include "clsDate.h"
#include "clsBankClient.h"
#include "clsUtil.h"


using namespace std;


class clsUser : public clsPerson
{

private:

	struct stLoginRegisterRecord;
	struct stTransferLog;

	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };

	enMode _Mode;
	int _Permissions;
	string _Password;
	string _UserName;

	bool _MarkToDelete = false;

	static clsUser _ConvertLinetoUsertObject(string Line, string Seperator = "#//#")
	{
		vector <string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stod(vUserData[6]));
	}

	static string _ConvertObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string Line = "";

		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User.UserName + Seperator;
		Line += clsUtil::EncryptText(User.Password)+ Seperator;
		Line += to_string(User.Permissions);

		
		return Line;
	}

	static vector <clsUser> _LoadDataFromFileToObject()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsUser User = _ConvertLinetoUsertObject(Line);

				vUsers.push_back(User);
			}

			MyFile.close();

		}

		return vUsers;

	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}

	void _Update()
	{
		vector <clsUser> _vUsers = _LoadDataFromFileToObject();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}
		}
		SaveToFile(_vUsers);
	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _SaveToFileAfterDelete(vector <clsUser> vUsers)
	{
		string UsersData = "";

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsUser& U : vUsers)
			{
				if (U._MarkToDelete == false)
				{
					UsersData = _ConvertObjectToLine(U);
					MyFile << UsersData << endl;
				}
			}
			MyFile.close();
		}
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string _ConvertLoginsToLine(string Seperator = "#//#")
	{
		string DataLine = "";

		DataLine += clsDate::DateToString(clsDate());
		DataLine += clsDate::GetSystemDateHourMinSec() + Seperator;
		DataLine += UserName + Seperator;
		DataLine += clsUtil::EncryptText(Password) + Seperator; 
		DataLine += to_string(Permissions); 

		return DataLine;
	}

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);

		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.Username = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]); 
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	

	static string _ConvertTransfaresToLine(string Seperator = "#//#", double Amount = 0, clsBankClients Client1 = clsBankClients()
		, clsBankClients Client2 = clsBankClients(), string Username = "")
	{
		string stDataForTransfareLog = "";

		stDataForTransfareLog += clsDate::DateToString(clsDate());
		stDataForTransfareLog += clsDate::GetSystemDateHourMinSec() + Seperator;
		stDataForTransfareLog += Client1.AccountNumber() + Seperator;
		stDataForTransfareLog += Client2.AccountNumber() + Seperator;
		stDataForTransfareLog += to_string(Amount) + Seperator;
		stDataForTransfareLog += to_string(Client1.AccountBalance) + Seperator;
		stDataForTransfareLog += to_string(Client2.AccountBalance) + Seperator;
		stDataForTransfareLog += Username;

		return stDataForTransfareLog;
	}


	static stTransferLog _ConvertTransferLoginLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLog TranferLog;;

		vector <string> vTransferLine = clsString::Split(Line, Seperator);

		TranferLog.DateTime = vTransferLine[0];
		TranferLog.SourceAcct = vTransferLine[1];
		TranferLog.DesAcct = vTransferLine[2];
		TranferLog.Amount = stod(vTransferLine[3]);
		TranferLog.SourceBal = stod(vTransferLine[4]);
		TranferLog.DesBal = stod(vTransferLine[5]);
		TranferLog.Username = vTransferLine[6];

		return TranferLog;
	}





public:

	struct stLoginRegisterRecord
	{
		string DateTime;
		string Username;
		string Password;
		int Permissions;
	};

	struct stTransferLog
	{
		string DateTime;
		string SourceAcct;
		string DesAcct;
		double Amount;
		double SourceBal;
		double DesBal;
		string Username;
	};

	enum enUserPermission {
		pAll = -1, pShowList = 1, pAddClient = 2,
		pDeleteClient = 4, pUpdateClient = 8,
		pFindClient = 16, pTransactions = 32,
		pManageUsers = 64, pRegister = 128
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string UserName, string Password, int Permissions)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Permissions = Permissions;
		_Password = Password;
		_UserName = UserName;
	}

	bool MarkedForDeleted()
	{
		return _MarkToDelete;
	}

	string GetUserName()
	{
		return _UserName;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
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

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static vector <clsUser> GetUserRecord()
	{
		return _LoadDataFromFileToObject();
	}

	bool IsEmptyUser()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static bool IsUserExist(string Username)
	{
		clsUser User1 = clsUser::Find(Username);
		return (!User1.IsEmpty());

	}

	static clsUser Find(string Username)
	{
		vector <clsUser> vUsers;
		string Line;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUsertObject(Line);
				if (User._UserName == Username)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string Username, string Password)
	{
		vector <clsUser> vUsers;
		string Line;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUsertObject(Line);
				if (User._UserName == Username && User._Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	enum enSaveUserResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2 };

	enSaveUserResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{

			if (IsEmptyUser())
			{
				return enSaveUserResults::svFaildEmptyObject;
			}
			break;
		}
		case enMode::UpdateMode:
		{
			_Update();

			return enSaveUserResults::svSucceeded;
		}

		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(UserName))
			{
				return enSaveUserResults::svFaildUserNameExists;
			}
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;
				return enSaveUserResults::svSucceeded;
			}

		}



		}




	}

	static void SaveToFile(vector <clsUser>& vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string UserData = "";

		if (MyFile.is_open())
		{
			for (clsUser U : vUsers)
			{
				UserData = _ConvertObjectToLine(U);
				MyFile << UserData << endl;
			}

		}
		MyFile.close();
	}

	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadDataFromFileToObject();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkToDelete = true;
				break;
			}

		}

		_SaveToFileAfterDelete(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}

	bool CheckAccessPermission(enUserPermission Permission)
	{
		if (_Permissions == enUserPermission::pAll)
			return true;

		return (_Permissions & Permission) == Permission;
	}

	void LoginFile()
	{
		fstream LoginFile;
		LoginFile.open("LoginRegister.txt", ios::out | ios::app);
		string DataFile = _ConvertLoginsToLine();

		if (LoginFile.is_open())
		{
			LoginFile << DataFile << endl;
		}

		LoginFile.close();
	}

	static vector <stLoginRegisterRecord> GetRegisterRecord()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;
		stLoginRegisterRecord LoginRegisterRecord;

		fstream LoginFile;
		LoginFile.open("LoginRegister.txt", ios::in);

		if (LoginFile.is_open())
		{
			string Line = "";

			while (getline(LoginFile, Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			LoginFile.close();
		}

		return vLoginRegisterRecord;
	}

	static void TransfareLoginFile(double Amount, clsBankClients Client1, clsBankClients Client2, string Username)
	{
		fstream TransfareFile;
		TransfareFile.open("TransfareLog.txt", ios::out | ios::app);
		string DataFile = _ConvertTransfaresToLine("#//#", Amount, Client1, Client2, Username);

		if (TransfareFile.is_open())
		{
			TransfareFile << DataFile << endl;
		}

		TransfareFile.close();
	}

	static vector <stTransferLog> GetTransferRecord()
	{
		vector <stTransferLog> vTransferLogRecord;
		stTransferLog TransferLogRecord;

		fstream TransferFile;
		TransferFile.open("TransfareLog.txt", ios::in);

		if (TransferFile.is_open())
		{
			string Line = "";

			while (getline(TransferFile, Line))
			{
				TransferLogRecord = _ConvertTransferLoginLineToRecord(Line);
				vTransferLogRecord.push_back(TransferLogRecord);
			}

			TransferFile.close();
		}

		return vTransferLogRecord;
	}









};

