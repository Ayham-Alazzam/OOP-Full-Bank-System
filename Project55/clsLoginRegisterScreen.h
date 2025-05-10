#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsLoginScreen.h"

class clsLoginRegisterScreen : protected clsScreen 
{
private:

    static void _PrintRegisterRecordForTable(clsUser::stLoginRegisterRecord stUserRegister)
    {
        cout << "| " << left << setw(30) << stUserRegister.DateTime;
        cout << "| " << left << setw(20) << stUserRegister.Username;
        cout << "| " << left << setw(15) << stUserRegister.Password;
        cout << "| " << left << setw(25) << stUserRegister.Permissions << "|\n";
    }

public:

    static void ShowRegisterLoginScreen()
    {
        if (!CheckAccessRights(clsUser::enUserPermission::pRegister))
        {
            return;
        }

        clsScreen::_DrawScreenHeader("Login Register");

        vector<clsUser::stLoginRegisterRecord> UserRegister = clsUser::GetRegisterRecord();

        string Title = "\t\t\tLogin Register Screen";
        string SubTitle = "\t\t\t(" + to_string(UserRegister.size()) + ") Login(s).";

        cout << "\n" << Title << endl;
        cout << SubTitle << endl;

        cout << "\n_________________________________________________________________________________________\n";
        cout << "| " << left << setw(30) << "Date Time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(15) << "Password";
        cout << "| " << left << setw(25) << "Permission" << "|\n";
        cout << "_________________________________________________________________________________________\n";

        if (UserRegister.empty())
        {
            cout << "\t\t\tNo Logins Available In the System!\n";
        }
        else
        {
            for (clsUser::stLoginRegisterRecord R : UserRegister)
            {
                _PrintRegisterRecordForTable(R);
            }

            cout << "_________________________________________________________________________________________\n";
        }
    }



};
