#pragma once

#include <vector>
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsFindUserScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"



using namespace std;


class clsManageUsersScreen : protected clsScreen
{

private:

	enum enManageUsersMenue { enListUser = 1, enAddNewUser = 2,
		                    enDeleteUser = 3, enUpdateUser = 4,
		                    enFindUser = 5, enuMainMenue = 6 };

	static short ReadManageUsersOption()
	{
		short Choice;
		cout << "Choose What Do You Want To Do? [1-6].\n";
		Choice = clsInputValidate::ReadIntNumber();
		return Choice;
	}

	static void _BackToManageUsers()
	{
		cout << "\n\nPress any key to go back to Manage Screen...";
		system("pause>0");
		system("cls");
		ManageUsersMenueScreen(); 
	}

	static void _PrintUsersList()
	{
		clsUsersListScreen::PrintUsersList();
	}

	static void _AddNewUser()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen(); 
	}

	static void _UpdateUserRecord()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen(); 
	}

	static void _DeleteUsersFromRecord()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _FindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen(); 
	}

	static void _ChooseManageUsersMenue(enManageUsersMenue MenueChoice) 
	{
	

		switch (MenueChoice)
		{
		case enManageUsersMenue::enListUser:
		{
			system("cls");
			_PrintUsersList();
			_BackToManageUsers();
			break;
		}
		case enManageUsersMenue::enAddNewUser:
		{
			system("cls");
			_AddNewUser();
			_BackToManageUsers();
			break;
		}
		case enManageUsersMenue::enDeleteUser:
		{
			system("cls");
			_DeleteUsersFromRecord();
			_BackToManageUsers();
			break;
		}
		case enManageUsersMenue::enUpdateUser:
		{
			system("cls");
			_UpdateUserRecord();
			_BackToManageUsers();
			break;
		}
		case enManageUsersMenue::enFindUser:
		{
			system("cls");
			_FindUserScreen();
			break;
		}
		case enManageUsersMenue::enuMainMenue:
		{
			// I supose to do nothing here :)
		}


		}


	}



public:

	static void ManageUsersMenueScreen()
	{
		if (!CheckAccessRights(clsUser::enUserPermission::pManageUsers)) 
		{
			return;
		}


		_DrawScreenHeader("Manage Users Screen");

		cout << "====================================================\n";
		cout << "\t\tManage Users Menue Screen\n";
		cout << "====================================================\n";
		cout << "\t[1] List Users.\n";
		cout << "\t[2] Add New User.\n";
		cout << "\t[3] Delete User.\n";
		cout << "\t[4] Update User's Info.\n";
		cout << "\t[5] Find User.\n";
		cout << "\t[6] Main Menue.\n";
		cout << "====================================================\n";

		_ChooseManageUsersMenue((enManageUsersMenue)ReadManageUsersOption() );
	}


};

