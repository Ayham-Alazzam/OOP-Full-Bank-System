#pragma once

#include "clsString.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class clsCurrency
{

private:

	enum enMode { EmptyMode = 1, UpdateMode = 2 };
	enMode _Mode;  

	string _Country;
	string _CurrencyCode; 
	string _CurrencyName; 
	float _Rate; 

	static clsCurrency _ConvertLinetoCurrencyObjec(string Line,string Separetor ="#//#")
	{
		vector <string> vData = clsString::Split(Line,Separetor); 

		return clsCurrency(enMode::UpdateMode,vData[0], vData[1], vData[2], stod(vData[3])); 
	}

	static string _ConverCurrencyObjectToLine(clsCurrency Currency ,string Separator = "#//#")
	{  
		string stCurrencyObjectData = ""; 

		stCurrencyObjectData += Currency.Country() + Separator;
		stCurrencyObjectData += Currency.CurrencyCode() +Separator;
		stCurrencyObjectData += Currency.CurrencyName() + Separator;
		stCurrencyObjectData += to_string(Currency.CurrencyRate());

		return stCurrencyObjectData; 
	}

	static vector <clsCurrency> _LoadCurrencysDataFromFile()
	{
		vector <clsCurrency> Currencys; 

		fstream CurrencyFile;
		CurrencyFile.open("Currencies.txt",ios::in); 

		if (CurrencyFile.is_open())
		{
			string Line = "";
			while (getline(CurrencyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObjec(Line); 
				Currencys.push_back(Currency);
			}
			CurrencyFile.close();
		}
		return Currencys; 
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys) 
	{
		fstream CurrencyFile;
		CurrencyFile.open("Currencies.txt", ios::out);
		string DataLine = ""; 

		if (CurrencyFile.is_open())
		{
			for (clsCurrency C : vCurrencys) 
			{
				DataLine = _ConverCurrencyObjectToLine(C);
				CurrencyFile << DataLine << endl; 
			}
			CurrencyFile.close();
		}

	}

	void _Update()
	{
		vector <clsCurrency> vCurrencys; 
		vCurrencys = _LoadCurrencysDataFromFile(); 

		for (clsCurrency &C : vCurrencys) 
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break; 
			}
		}
		_SaveCurrencyDataToFile(vCurrencys);

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "","","",0);
	}



public:

	clsCurrency(enMode Mode,string Country,string CurrencyCode,string CurrencyName,float Rate)
	{
		_Mode  = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode; 
		_CurrencyName = CurrencyName;
		_Rate = Rate; 
	} 

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float CurrencyRate()
	{
		return _Rate;       
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode); 
		vector <clsCurrency> Currencys = _LoadCurrencysDataFromFile(); 

		fstream CurrencyFile;
		CurrencyFile.open("Currencies.txt",ios::in); 
		string Line = "";

		if (CurrencyFile.is_open())
		{
			while (getline(CurrencyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObjec(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					CurrencyFile.close();
					return Currency;
				}

			}
			CurrencyFile.close();   
		}

		return _GetEmptyCurrencyObject(); 

	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream CurrencyFile;
		CurrencyFile.open("Currencies.txt", ios::in);

		if (CurrencyFile.is_open())
		{
			string Line;
			while (getline(CurrencyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObjec(Line); 
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					CurrencyFile.close();
					return Currency;
				}

			}
			CurrencyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());

	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencysDataFromFile();
	}

	float ConvertToUSD(float Amount) 
	{
		return (float) Amount / CurrencyRate();  

	}

	float ConvertToAnotherCurrency(float Amount,clsCurrency Cerrancy2) 
	{
		Amount = ConvertToUSD(Amount); 

		if (Cerrancy2.CurrencyCode() == "USD") 
			return Amount;

		return (float)(Amount * Cerrancy2.CurrencyRate()); 
	}



};
