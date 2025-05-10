#pragma once

#include <iostream>
#include <vector>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;



class clsClientListScreen : protected clsScreen
{
	
private:
	 
	static void _PrintClientRecordForTable(clsBankClients Client) //add (s)
	{
		cout << "| " << left << setw(20) << Client.AccountNumber();
		cout << "| " << left << setw(15) << Client.PinCode;
		cout << "| " << left << setw(30) << Client.FirstName + " " + Client.LastName;
		cout << "| " << left << setw(15) << Client.Phone;
		cout << "| " << left << setw(15) << Client.AccountBalance;
	}


public:

	static void PrintClientsList() 
	{ 

		if (!CheckAccessRights(clsUser::enUserPermission::pShowList))
		{
			return;
		}

		vector <clsBankClients> Clients = clsBankClients::GetClientRecord();

		clsScreen::_DrawScreenHeader("  Client's List","for ["+ to_string(Clients.size())+"] Client(s)");
		cout << "\n____________________________________________________________________________________";
		cout << "______________________\n\n";
		cout << "| " << left << setw(20) << "Account Number ";
		cout << "| " << left << setw(15) << "Pin Code ";
		cout << "| " << left << setw(30) << "Name";
		cout << "| " << left << setw(15) << "Phone";
		cout << "| " << left << setw(15) << "Account Balance";
		cout << "\n____________________________________________________________________________________";
		cout << "______________________\n\n";

		for (clsBankClients C : Clients)
		{
			_PrintClientRecordForTable(C); 
			cout << endl;
		}
	}




};

