#pragma once

#include <vector>
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;


class clsCurrenciesListScreen : protected clsScreen 
{
private:


    static void _PrintCurrencyRecordForTable(clsCurrency Currency)
    {
        cout << "| " << left << setw(30) << Currency.Country();
        cout << "| " << left << setw(15) << Currency.CurrencyCode();
        cout << "| " << left << setw(40) << Currency.CurrencyName();
        cout << "| " << left << setw(15) << Currency.CurrencyRate();
        cout << "|\n";
    }

public:

    static void PrintCurrencyList()      
    {
        clsScreen::_DrawScreenHeader("Currency List Screen");

        vector <clsCurrency> Currencies = clsCurrency::GetCurrenciesList(); 

        string Title = "\t  Currency List Screen"; 
        string SubTitle = "\t    (" + to_string(Currencies.size()) + ") Currency(s).";

        cout << "\n\n\t\t\t\t\t" << Title << endl;
        cout << "\t\t\t\t\t" << SubTitle << endl;
        cout << "\n_______________________________________________________________________________________________________________\n";

        cout << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(15) << "Code";
        cout << "| " << left << setw(40) << "Name";
        cout << "| " << left << setw(15) << "Rate $";
        cout << "|\n";
        cout << "_______________________________________________________________________________________________________________\n";

        for (clsCurrency C : Currencies) 
        {
            _PrintCurrencyRecordForTable(C); 
        }

        cout << "_______________________________________________________________________________________________________________\n";
    }







};

