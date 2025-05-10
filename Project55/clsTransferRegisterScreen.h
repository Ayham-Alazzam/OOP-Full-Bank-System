#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsLoginScreen.h"

class clsTransferRegisterScreen : protected clsScreen
{
private:

    static void _PrintTransferRecordForTable(clsUser::stTransferLog TransferRegister)
    {
     
        cout << "| " << left << setw(20)  << TransferRegister.DateTime;
        cout << "| " << left << setw(15)  << TransferRegister.SourceAcct;
        cout << "| " << left << setw(15)  << TransferRegister.DesAcct;
        cout << "| " << right << setw(10) << TransferRegister.Amount;
        cout << "| " << right << setw(12) << TransferRegister.SourceBal;
        cout << "| " << right << setw(12) << TransferRegister.DesBal;
        cout << "| " << left << setw(15)  << TransferRegister.Username << " |\n";
    }

public:

    static void ShowTransferLoginScreen()
    {
        clsScreen::_DrawScreenHeader("Transfer Register Screen");

        vector<clsUser::stTransferLog> vTransferRegister = clsUser::GetTransferRecord();

        string Title = "\t\tTransfer Register Screen";
        string SubTitle = "\t\t(" + to_string(vTransferRegister.size()) + ") Transfer(s).";

        cout << "\n" << Title << endl;
        cout << SubTitle << endl;

        cout << "\n";
        cout << "| " << left << setw(20) << "DateTime";
        cout << "| " << left << setw(15) << "SourceAcct";
        cout << "| " << left << setw(15) << "DesAcct";
        cout << "| " << right << setw(10) << "Amount";
        cout << "| " << right << setw(12) << "SourceBal";
        cout << "| " << right << setw(12) << "DesBal";
        cout << "| " << left << setw(15) << "Username" << " |\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n"; 

        for (clsUser::stTransferLog T : vTransferRegister)
        {
            _PrintTransferRecordForTable(T);
        }

        cout << "------------------------------------------------------------------------------------------------------------------------\n"; 
    }





};
