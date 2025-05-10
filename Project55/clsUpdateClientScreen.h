#pragma once

#include <vector>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;





class clsUpdateClientScreen : clsScreen
{

private:

    static void _ReadClientInfo(clsBankClients& Client,string AccountNumber)
    {
        Client.AccountNumber() = AccountNumber;

        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();


        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();


        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();


        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();


        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();


        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();

    }

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
     
    static void UpdateClientInfo() 
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
        cout << "Sure you want to update this client's info? (Y/N). ";
        cin >> Answer;
    
       if (Answer == 'y' || Answer == 'Y')
       {
    
           cout << "\n\nUpdate Client Info:";
           cout << "\n____________________\n";
    
    
           _ReadClientInfo(Client1,AccountNumber);
    
           clsBankClients::enSaveResults SaveResult;
    
           SaveResult = Client1.Save();
    
           switch (SaveResult)
           {
           case  clsBankClients::enSaveResults::svSucceeded:
           {
               cout << "\nAccount Updated Successfully :-)\n";
    
               _PrintClient(Client1);
               break;
           }
           case clsBankClients::enSaveResults::svFaildEmptyObject:
           {
               cout << "\nError account was not saved because it's Empty";
               break;
    
           }
    
           }
    
       }

    }







};







    




