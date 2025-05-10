#pragma once

#include <vector>
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsTransferRegisterScreen.h"

using namespace std;


class clsTransactionsScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClients Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName      : " << Client.FirstName;
		cout << "\nLastName       : " << Client.LastName;
		cout << "\nFull Name      : " << Client.FirstName + " " + Client.LastName;
		cout << "\nEmail          : " << Client.Email;
		cout << "\nPhone          : " << Client.Phone;
		cout << "\nAccount Number : " << Client.AccountNumber();
		cout << "\nPassword       : " << Client.PinCode;
		cout << "\nBalance        : " << Client.AccountBalance;
		cout << "\n___________________\n";

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

	static void _ShowTransactionsMenueScreen()
	{
		cout << "====================================================\n";
		cout << "\t\tTransactions Menue Screen\n";
		cout << "====================================================\n";
		cout << "\t[1] Deposite.\n";
		cout << "\t[2] With Draw.\n";
		cout << "\t[3] Total Balances.\n";
		cout << "\t[4] Transfare.\n";
		cout << "\t[5] Transfare Log.\n";
		cout << "\t[6] Main Menue.\n";
		cout << "====================================================\n";
	}

	static void _BackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Main Menue...";
		system("pause>0");
		system("cls");
		_ShowTransactionsMenueScreen();
	}

	static void _ShowMenueScreen()
	{
		cout << "====================================================\n";
		cout << "\t\tMain Menue Screen\n";
		cout << "====================================================\n";
		cout << "\t[1] Show Client's List.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delete Client.\n";
		cout << "\t[4] Update Client's Info.\n";
		cout << "\t[5] Find Clients.\n";
		cout << "\t[6] Transactions.\n";
		cout << "\t[7] Manage Users.\n";
		cout << "\t[8] Login Rigester.\n";
		cout << "\t[9] Show Currency Screen.\n";
		cout << "\t[10] Logout.\n";
		cout << "====================================================\n";
	}

	static void _BackToMenue()
	{
		cout << "\n\nPress any key to go back to Main Menue...";
		system("pause>0");
		system("cls");
		_ShowMenueScreen();
	}

	static void _PrintTransactionsList(vector <clsBankClients> Clients)
	{
		cout << "\n\n\t\t\t\t\tClient List (" << Clients.size() << ") Cliient(s)\n";
		cout << "\n____________________________________________________________________________________";
		cout << "______________________\n\n";
		cout << "| " << left << setw(20) << "Account Number ";
		cout << "| " << left << setw(30) << "Name";
		cout << "| " << left << setw(15) << "Account Balance";
		cout << "\n____________________________________________________________________________________";
		cout << "______________________\n\n";

		for (clsBankClients C : Clients)
		{
			cout << "| " << left << setw(20) << C.AccountNumber();
			cout << "| " << left << setw(30) << C.FirstName + " " + C.LastName; 
			cout << "| " << left << setw(15) << C.AccountBalance; 
			cout << endl;
		}
	}

	static void _Deposite()
	{
		vector <clsBankClients> Clients = clsBankClients::GetClientRecord();
		double Amount = 0;
		char sure = 'n';

		string AccountNumber = "";
		cout << "Enter Account Number? ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClients::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Not Exist, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClients Client1 = clsBankClients::Find(AccountNumber);
		_PrintClient(Client1);

		cout << "\n\nEnter Deposit Amount:\n";
		cin >> Amount;
		cout << "Are you sure you want to perform this transaction? (Y/N)\n";
		cin >> sure;

		if (sure == 'y' || sure == 'Y')
		{

			for (clsBankClients & C : Clients)
			{
				if (C.AccountNumber() == Client1.AccountNumber())
				{
					C.AccountBalance += Amount;
					break;
				}
			}


			fstream ClientFile("Clients.txt", ios::out);
			if (ClientFile.is_open())
			{
				for (clsBankClients C : Clients)
				{
					ClientFile << _ConvertObjectToLine(C) << endl;
				}
				ClientFile.close();
			}

			cout << "Deposit completed successfully.\n";
			_PrintClient(Client1);
		}
	}

	static void _WithDraw()
	{
		vector <clsBankClients> Clients = clsBankClients::GetClientRecord(); 
		clsBankClients Client;  
		double Amount = 0; 
		char sure = 'n'; 

		string AccountNumber = "";
		cout << "Enter Account Number? ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClients::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Not Exist, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClients Client1 = clsBankClients::Find(AccountNumber);
		_PrintClient(Client1);


		cout << "\n\nEnter Withdrawal Amount:\n";
		cin >> Amount;

		if (Amount > Client1.AccountBalance)
		{
			cout << "Insufficient funds!\n";
			return;
		}

		cout << "Are you sure you want to perform this transaction? (Y/N)\n";
		cin >> sure;

		if (sure == 'y' || sure == 'Y')
		{

			for (clsBankClients & C : Clients)
			{
				if (C.AccountNumber() == Client1.AccountNumber())
				{
					C.AccountBalance -= Amount;
					break;
				}
			}


			fstream ClientFile("Clients.txt", ios::out);
			if (ClientFile.is_open())
			{
				for (clsBankClients C : Clients)
				{
					ClientFile << _ConvertObjectToLine(C) << endl; 
				}
				ClientFile.close();
			}

			cout << "Withdrawal completed successfully.\n";
			_PrintClient(Client1);   
		}
	}

	static void _Transfare()
	{
		vector <clsBankClients> Clients = clsBankClients::GetClientRecord();
		clsBankClients Client;
		double Amount = 0;
		double Transfare = 0;
		char sure = 'n';

		string AccountNumber = "";
		cout << "Enter Account Number To transfare from? ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClients::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Not Exist, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClients Client1 = clsBankClients::Find(AccountNumber);
		_PrintClient(Client1);

		cout << "\n\nEnter Transfare Amount:\n";
		cin >> Amount;

		while (Amount > Client1.AccountBalance)
		{
			cout << "Insufficient funds!\n";
			cout << "Enter Transfare Amount: ";
			cin >> Amount;   
		}

		cout << "Sure? (Y/N).";
			cin >> sure;
			if (sure == 'Y' || sure == 'y')
			{
				Client1.AccountBalance -= Amount;
				Transfare += Amount;

				for (clsBankClients &C1 : Clients)
				{
					if (C1.AccountNumber() == Client1.AccountNumber())
					{
						C1 = Client1;
						clsBankClients::SaveToFile(Clients);  
						break;
					}
				}
			}
			else
				_BackToMenue();

		AccountNumber = ""; 
		cout << "Enter Account Number To Transfare To? "; 
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClients::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Not Exist, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClients Client2 = clsBankClients::Find(AccountNumber);
		_PrintClient(Client2); 

		cout << "Sure? (Y/N).";
		cin >> sure;
		if (sure == 'Y' || sure == 'y')
		{
			Client2.AccountBalance += Transfare;

			for (clsBankClients &C2 : Clients)
			{
				if (C2.AccountNumber() == Client2.AccountNumber())
				{
					C2 = Client2;
					clsBankClients::SaveToFile(Clients);  
					break;
				}
			}
		}
		else
			_BackToMenue(); 

		clsUser::TransfareLoginFile(Amount,Client1,Client2,CurrentUser.UserName);  

		_PrintClient(Client1);
		_PrintClient(Client2);
	}

    static double _CalculateTotalBalances(vector <clsBankClients> Clients)
	{
		double sumBalance = 0;
		for (clsBankClients C : Clients) 
		{
			sumBalance += C.AccountBalance;
		}
		return sumBalance;
	}

	static void _ShowTotalBalances()
	{
		vector <clsBankClients> Clients = clsBankClients::GetClientRecord();
		double sumBalance = _CalculateTotalBalances(Clients);
		_PrintTransactionsList(Clients);
		cout << "\n\n\t\t\tTotal Balances = " << sumBalance << endl;
	}
	
	static void _DepositeScreen()
	{
		clsScreen::_DrawScreenHeader("Deposite Screen");
		_Deposite();
	}

	static void _WithDrawScreen()
	{
		clsScreen::_DrawScreenHeader("Wuthdraw Screen");
		_WithDraw();
	}

	static void _TransfareScreen()
	{
		clsScreen::_DrawScreenHeader("Transfare Screen");
		_Transfare();
	}

	static void _TransfareLoginScreen()
	{
		clsTransferRegisterScreen::ShowTransferLoginScreen();
	}

public:

	enum enTransactionsChoices {enDeposite = 1, enWithDraw = 2,
	                            enTotalBalances = 3,enTransfare = 4,
	                            enTransfareLogin = 5, enMainMenue = 6};   
	 
	static void ChooseTransactionsMenueChoice()
	{

		if (!CheckAccessRights(clsUser::enUserPermission::pShowList))
		{
			return;
		}


		enTransactionsChoices TransactionsChoices;
		vector <clsBankClients> Clients = clsBankClients::GetClientRecord();
		string AccountNumber = "";
		clsBankClients Client;

		clsScreen::_DrawScreenHeader("Transactions Menue");

		short Choice;
		_ShowTransactionsMenueScreen();
		cout << "Choose What Do You Want To Do? [1-6].\n";
		cin >> Choice;

		switch (Choice)
		{
		case enTransactionsChoices::enDeposite:
		{
			system("cls");
			_DepositeScreen(); 
			_BackToTransactionsMenue(); 
			break; 
		}
		case enTransactionsChoices::enWithDraw:
		{
			system("cls");
			_WithDrawScreen();
			_BackToTransactionsMenue();
			break;
		}
		case enTransactionsChoices::enTotalBalances:
		{
			system("cls");
			_ShowTotalBalances();
			_BackToTransactionsMenue();
			break;
		}
		case enTransactionsChoices::enTransfare:
		{
			system("cls");
			_TransfareScreen();
			_BackToTransactionsMenue();
			break;
		} 
		case enTransactionsChoices::enTransfareLogin:
		{
			system("cls");
			_TransfareLoginScreen();
			_BackToTransactionsMenue();
			break;
		}

		case enTransactionsChoices::enMainMenue:
		{
			system("cls");
			_BackToMenue(); 
			break;
		}

		}

	}




};

