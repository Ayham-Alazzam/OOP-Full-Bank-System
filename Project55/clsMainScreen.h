#pragma once


#include <iomanip>
#include <iostream>
#include "Global.h"
#include "clsScreen.h"
#include "clsDeleteClient.h "
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsFindClientScreen.h"
#include "clsManageUsersScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsCurrencyMainScreen.h"
#include "clsLoginRegisterScreen.h"


using namespace std; 
					 

class clsMainScreen : protected clsScreen
{	

private:

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
		cout << "\t[8] Show Login Register Screen.\n";
		cout << "\t[9] Show Currency Screen.\n";
		cout << "\t[10] Logout.\n";
		cout << "====================================================\n";
	}
	 
	static int  _ChooseMenueOption()
	{
		int Choice;
		cout << "Enter your choice [1-10]? ";
		Choice = clsInputValidate::ReadIntNumberBetween(1, 10); 
		return Choice; 
	}
	 
	static void _PrintClientsList()
	{
		clsClientListScreen::PrintClientsList();

	}
	 
	static void _BackToMenue()
	{
		cout << "\n\nPress any key to go back to Main Menue...";
		system("pause>0");
		system("cls");
		_ShowMenueScreen();
	}
	
	static void _ReadNewClient()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen(); 
	}
	 
	static void _DeleteClientFromRecord()
	{
		clsDeleteClient::DeleteClientScreen();
	}
	 
	static void _UpdateClientRecord()  
	{
		clsUpdateClientScreen::UpdateClientInfo();
	}
	 
	static void _SearchByAccountNumber()
	{
		clsFindClientScreen::FindClient();
	}
	 
	static void _PrintClientRecord()
	{
		cout << "Will be here\n";
	}
	 
	static void _ChooseTransactionsMenueChoice()
	{
		cout << "Will be here\n";
	}
	 
	static void _ChooseManageUsers()
	{
		clsManageUsersScreen::ManageUsersMenueScreen();
	}

	static void _ShowTransactionsMenueScreen()
	{
		clsTransactionsScreen::ChooseTransactionsMenueChoice();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowRegisterLoginScreen(); 
	}

	static void _ShowCurrencyScreen()
	{
		clsCurrencyMainScreen::ShowCurrencyChoiceMenueScreen(); 
	}

	static void _Logout()
	{
		clsScreen::_DrawScreenHeader("See You :)");
		CurrentUser = clsUser::Find("","");
	}



public:

	enum enMenueChoices { enShowClientList = 1, enAddNewClient = 2,
		                  enDleteClient = 3, enUpdateClientInfo = 4,
		                  enFindClient = 5, enTransactions = 6,
		                  enManageUsers = 7,enLoginRegister = 8,enCurrencyScreen,enLogout = 10 };          


	static void ChooseMeneuChoice()
	{
		int Choice;
		int AccountNumber;

		while (true)
		{
			clsScreen::_DrawScreenHeader("Main Menue","");
			_ShowMenueScreen();
		    Choice = _ChooseMenueOption();
			switch (Choice)
			{
			case enMenueChoices::enShowClientList:
			{	
		    	 system("cls");
		    	_PrintClientsList();  
		    	_BackToMenue();
		    	 break;
			
			}
			case enMenueChoices::enAddNewClient:
			{
				    system("cls"); 
					_ReadNewClient(); 
					_BackToMenue();  
					break;
				
			}
			case enMenueChoices::enDleteClient:
			{	
					system("cls");
					_DeleteClientFromRecord();
					_BackToMenue();
					break;
			
			
			}
			case enMenueChoices::enUpdateClientInfo:
			{		
					system("cls");
					_UpdateClientRecord();
					_BackToMenue(); 
					break;
			
			}
			case enMenueChoices::enFindClient:
			{	
		    		 system("cls");
					_SearchByAccountNumber();
					_BackToMenue();  
					break;
			}
			case enMenueChoices::enTransactions:
			{
					 system("cls");
				    _ShowTransactionsMenueScreen();
				    _BackToMenue();     
					break;
				
			}
			case enMenueChoices::enManageUsers:
			{
					system("cls");
					_ChooseManageUsers(); 
					_BackToMenue();       
					break;
				
			}

			case enMenueChoices::enLoginRegister:
			{
				system("cls");
				_ShowLoginRegisterScreen();
				_BackToMenue();
				break;
			}
			case enMenueChoices::enCurrencyScreen:
			{
				system("cls");
				_ShowCurrencyScreen();
				_BackToMenue();
				break;
			}

			case enMenueChoices::enLogout:
			{
				system("cls");
				_Logout();
				exit(0); 
				break;
			}

			}
			system("cls");
		}
	}






};					 
					 
					 
