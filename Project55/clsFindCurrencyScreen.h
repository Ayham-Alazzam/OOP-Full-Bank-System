#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
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


public:

    static void ShowFindCurrencyScreen()
    {
        short Answer = 1;
        _DrawScreenHeader("Find Currency Screen");
        cout << "Find By: [1] Code , [2] Country ?\n";
        cin >> Answer;

        if (Answer == 1)
        {
            string CurrencyCode = "";
            cout << "Enter Currency Code: ";
            CurrencyCode = clsInputValidate::ReadString(); 
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode); 
            _ShowResult(Currency); 
        }
        else
        {
            string CurrencyCountry = "";
            cout << "Enter Currency Code: ";
            CurrencyCountry = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(CurrencyCountry);
            _ShowResult(Currency);
        }


    }


};

