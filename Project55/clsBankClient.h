#pragma once

#include <string>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;


class clsBankClients : public clsPerson
{

private:

	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool   _MarkToDelte = false;


	static clsBankClients _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator); 

		return clsBankClients(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertObjectToLine(clsBankClients Client, string Seperator = "#//#")
	{
		string Line = "";

		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.AccountNumber() + Seperator;
		Line += Client.PinCode + Seperator;
		Line += to_string(Client.AccountBalance);

		return Line;
	}

	static vector <clsBankClients> _LoadDataFromFileToObject()
	{
		vector <clsBankClients> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsBankClients Client = _ConvertLinetoClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}

	static clsBankClients _GetEmptyClientObject()
	{
		return clsBankClients(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}

	void _Update()
	{
		vector <clsBankClients> _vClients = _LoadDataFromFileToObject();

		for (clsBankClients& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		SaveToFile(_vClients);
	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _SaveToFileAfterDelete(vector <clsBankClients> vClients)
	{
		string ClientData = "";

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankClients& C : vClients)
			{
				if (C._MarkToDelte == false)
				{
					ClientData = _ConvertObjectToLine(C);
					MyFile << ClientData << endl;
				}
			}
			MyFile.close();
		}
	}

public:

	clsBankClients()
	{

	}

	clsBankClients(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string AccountNumber, string PinCode, double AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FirstName + " " + LastName;
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClients Client1 = clsBankClients::Find(AccountNumber);
		return (!Client1.IsEmpty());

	}

	static clsBankClients Find(string AccountNumber)
	{
		vector <clsBankClients> vClients;
		string Line;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsBankClients Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClients Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClients> vClients;
		string Line;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				clsBankClients Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{

				return enSaveResults::svFaildEmptyObject;

			}

		}

		case enMode::UpdateMode:
		{


			_Update();

			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{

			if (clsBankClients::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}

	}

	static clsBankClients GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClients(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClients> vClients = _LoadDataFromFileToObject();
		for (clsBankClients& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkToDelte = true;
				break;
			}
		}
		_SaveToFileAfterDelete(vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClients> GetClientRecord()
	{
		return _LoadDataFromFileToObject();
	}

	static void SaveToFile(vector <clsBankClients>& vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		string ClientData = "";

		if (MyFile.is_open())
		{
			for (clsBankClients C : vClients)
			{
				ClientData = _ConvertObjectToLine(C);
				MyFile << ClientData << endl;
			}
		}
		MyFile.close();
	}


















};








