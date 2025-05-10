#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include <fstream>

using namespace std;




class clsLoginScreen : protected clsScreen
{

private:



	static void _Login()
	{
		bool LoginFailed = false;
		string Username = "";
		string Password = "";
		int CountLog = 3;

		do {

			if (CountLog == 1)
			{
				cout << "\n\nYou are LOCKED after 3 trials.\n";
				exit(0);
			}

			if (LoginFailed)
			{
				CountLog--;
				cout << "\nUsername/Password Invalide.\n";
				cout << "You have [" << CountLog << "] trials to Login.\n\n";
			}

			cout << "Enter Username: ";
			cin >> Username;
			cout << "Enter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username,Password);  

			LoginFailed = CurrentUser.IsEmptyUser();

		} while (LoginFailed);

		CurrentUser.LoginFile();   
		system("cls");      
		clsMainScreen::ChooseMeneuChoice();

	}






public:

	static void ShowLoginScreen()
	{
		 system("cls");
		_DrawScreenHeader("Login Screen");
		_Login();
		

	}



};

