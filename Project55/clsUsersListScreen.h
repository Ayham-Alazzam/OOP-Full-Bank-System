#pragma once

#include <iostream>
#include <vector>
#include "clsUser.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;


class clsUsersListScreen : protected clsScreen
{
private:


	static void _PrintUsersRecordForTable(clsUser User)
	{
		cout << "| " << left << setw(20) << (User.FirstName + " " + User.LastName);
		cout << "| " << left << setw(15) << User.Phone;
		cout << "| " << left << setw(25) << User.Email;
		cout << "| " << left << setw(15) << User.Password;
		cout << "| " << left << setw(12) << User.Permissions;
		cout << "|\n";
	}

	

public:

	static void PrintUsersList()
	{

        if (!CheckAccessRights(clsUser::enUserPermission::pShowList))
        {
            return;
        }


		vector <clsUser> Users = clsUser::GetUserRecord(); 

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(Users.size()) + ") User(s).";

        cout << "\n\n\t\t\t\t\t" << Title << endl;
        cout << "\t\t\t\t\t" << SubTitle << endl;
        cout << "\n_______________________________________________________________________________________________________________\n";

        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(15) << "Password";
        cout << "| " << left << setw(12) << "Permission";
        cout << "|\n";

        cout << "_______________________________________________________________________________________________________________\n";

        for (clsUser U : Users)
        {
            _PrintUsersRecordForTable(U);
        }

        cout << "_______________________________________________________________________________________________________________\n";
    }



};

