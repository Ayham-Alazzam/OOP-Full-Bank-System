#pragma once

#include <vector>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;



class clsDeleteClient : protected clsScreen
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

public:

    static void DeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enUserPermission::pShowList))
        {
            return;
        }



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
        
        char Answer = 'n';
        cout << "Sure you want to delete the client? (Y/N). ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client1.Delete())
            {
                cout << "Client Deleted Succesfuly.\n";
                _PrintClient(Client1);
            }
            else
                cout << "Error.\n";
        }

    }



};

