#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h" 
#include "clsInputValidate.h"

using namespace std; 



class clsUpdateCurrencyRateScreen : protected clsScreen 
{

private:


    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.CurrencyRate();

        cout << "\n_____________________________\n";

    }

    static void _ShowResult(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "Currency Was Found!\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
            
        }
    }

    static clsCurrency _ReadCurrencyCode()
    {
        string CurrencyCode = "";

        cout << "Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
       _ShowResult(Currency);

       return Currency; 
    }

    static void UpdateCurrencyRateForm()
    {
        cout << "\nUpdate Currency Rate:\n";
        cout << "\n----------------------------\n";
        cout << "\nEnter New Rate: ";
    }

public:

	static void UpdateCurrencyRateScreen()
	{

        _DrawScreenHeader("Update Currency Screen");

      char Answer = 'n';
      clsCurrency Currency = _ReadCurrencyCode(); 
      if (!Currency.IsEmpty())
      {
          cout << "Are you sure you want to Update this Currency? (Y/N). ";
          cin >> Answer;
          if (Answer == 'Y' || Answer == 'y')
          {
              float NewRate;
              UpdateCurrencyRateForm();
              NewRate = clsInputValidate::ReadDblNumber();
              Currency.UpdateRate(NewRate);
          }
      }


	} 



};

