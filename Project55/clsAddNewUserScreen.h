#pragma once

#include <vector>
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;



class clsAddNewUserScreen : protected clsScreen
{
private:

    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FirstName + " " + User.LastName; 
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char Answer = 'n';

        cout << "Do you want to give the User full permission? (Y/N). ";
        cin >> Answer; 

        if (Answer == 'Y' || Answer == 'y')
        {
            return -1;
        }
        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            Permissions += clsUser::enUserPermission::pShowList;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enUserPermission::pAddClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enUserPermission::pDeleteClient; 
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enUserPermission::pUpdateClient; 
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enUserPermission::pFindClient;  
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enUserPermission::pTransactions;   
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enUserPermission::pManageUsers;   
        }

        cout << "\nRegister Screen? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enUserPermission::pRegister; 
        }


        return Permissions; 
    }



public:

    static void ShowAddNewUserScreen()
    {
        if (!CheckAccessRights(clsUser::enUserPermission::pShowList))
        {
            return;
        }


        _DrawScreenHeader("\t  Add New User Screen"); 

        vector <clsUser> Users = clsUser::GetUserRecord();
        string Username = "";

        cout << "Enter Username: ";
        Username = clsInputValidate::ReadString(); 

        while (clsUser::IsUserExist(Username))
        {
            cout << "User is already exist, Enter another: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser NewUser= clsUser::GetAddNewUserObject(Username);

        _ReadUserInfo(NewUser); 

        clsUser::enSaveUserResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveUserResults::svSucceeded:
        {
            cout << "User Added Successfuly :)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveUserResults::svFaildUserNameExists: 
        {
            cout << "Error, Failed Because Username is Already Exist :(\n";
            break;
        }
        case clsUser::enSaveUserResults::svFaildEmptyObject: 
        {
            cout << "Error, Failed Because Object is Empty :(\n";
            break;
        }

        }




    }

};

