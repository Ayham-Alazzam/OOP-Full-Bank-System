#pragma once

#include <vector>
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsFindCurrencyScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"


using namespace std;


class clsCurrencyMainScreen : protected clsScreen
{

private:

	enum enCrrencyChoice { enListCurrencies =  1, enFindCurrencies = 2,
		enUpdateRate = 3, enCurrencyCalculator = 4,enMenueScreen = 5 }; 

	static void _ListCurrencies()
	{
		clsCurrenciesListScreen::PrintCurrencyList(); 
	}

	static void _FindCurrencies()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen(); 
	}

	static void _UpdateRate()
	{
		clsUpdateCurrencyRateScreen::UpdateCurrencyRateScreen(); 
	}

	static void _CurrencyCalculator()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen(); 
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
		cout << "\t[9] Logout.\n";
		cout << "====================================================\n";
	}

	static void _BackToMenue()
	{
		cout << "\n\nPress any key to go back to Main Menue...";
		system("pause>0");
		system("cls");
		_ShowMenueScreen();
	}

	static int  _ChooseMenueOption()
	{
		int Choice;
		cout << "Enter your choice [1-5]? ";
		Choice = clsInputValidate::ReadIntNumberBetween(1, 9);
		return Choice;
	}

	static void _ShowCurrencyMenueScreen()
	{
		cout << "====================================================\n";
		cout << "\t\tCurrency Menue Screen\n";
		cout << "====================================================\n";
		cout << "\t[1] List Currencies.\n";
		cout << "\t[2] Find Currency.\n";
		cout << "\t[3] Update Rate.\n";
		cout << "\t[4] Currency Calculator.\n";
		cout << "\t[5] Main Menue.\n";
		cout << "====================================================\n";
	}

	static void _BackToCurrencyMenueScreen()
	{

		cout << "\n\nPress any key to go back to Currency Menue Screen...";
		system("pause>0");
		system("cls");
		_ShowCurrencyMenueScreen();
	}

	static void _ChooseCurrencyMenue(enCrrencyChoice CrrencyChoice)
	{
		switch (CrrencyChoice)
		{
                   
		case enCrrencyChoice::enListCurrencies:
		{
			system("cls");
			_ListCurrencies();
			_BackToCurrencyMenueScreen();  
			break;
		}
		case enCrrencyChoice::enFindCurrencies:
		{
			system("cls");
			_FindCurrencies(); 
			_BackToCurrencyMenueScreen();
			break;
		}
		case enCrrencyChoice::enUpdateRate:
		{
			system("cls");
			_UpdateRate();  
			_BackToCurrencyMenueScreen();
			break;
		}
		case enCrrencyChoice::enCurrencyCalculator:
		{
			system("cls");
			_CurrencyCalculator(); 
			_BackToCurrencyMenueScreen();
			break;
		}
		case enCrrencyChoice::enMenueScreen:
		{
			system("cls");
			_BackToMenue(); 
			break;
		}



		}


	}



public:

	static void ShowCurrencyChoiceMenueScreen()
	{
		_DrawScreenHeader("Currency Menue Screen");
		_ShowCurrencyMenueScreen(); 
		_ChooseCurrencyMenue((enCrrencyChoice)_ChooseMenueOption());
	}




};

