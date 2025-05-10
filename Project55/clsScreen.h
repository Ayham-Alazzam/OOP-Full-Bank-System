#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
 
using namespace std;

class clsScreen
{

public:
	 
	static void _DrawScreenHeader(string Title,string SubTitle = "")
	{
		cout << "----------------------------------------------------\n\n";
		cout << "\n\t\t  " << Title << "\n\n";
		if (SubTitle != "")
		{
			cout << "\t\t" << SubTitle << "\n\n";
			cout << "\n\n";     
		}
		cout << "User: " << CurrentUser.UserName << endl; 
		cout << "Date : " << clsDate::DateToString(clsDate()); 
		cout << "\n----------------------------------------------------\n\n";
	} 

	static bool CheckAccessRights(clsUser::enUserPermission Permission)
	{
		if (!CurrentUser.CheckAccessPermission(Permission))     
		{
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________\n\n";
			return false;
		}
		else
		{
			return true;
		}


	}





};

