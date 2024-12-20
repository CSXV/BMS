#pragma once
#include "Header Files/clsString.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

string const CurrencyFileName{"Currencies.txt"};

class clsCurrency {
private:
  enum enMode { enEmptyMode = 0, enUpdateMode = 1 };
  enMode _Mode;
  string _Country;
  string _CurrencyCode;
  string _CurrencyName;
  float _Rate;

  static clsCurrency _ConvertLineToCurrencyObject(string Line,
                                                  string Seperator = "#//#") {
    vector<string> vClientData;
    vClientData = clsString::Split(Line, Seperator);

    return clsCurrency(enMode::enUpdateMode, vClientData[0], vClientData[1],
                       vClientData[2], stod(vClientData[3]));
  }

  static string _ConvertCurrencyObjectToLine(clsCurrency Currency,
                                             string Seperator = "#//#") {
    string UserRecord = "";

    UserRecord += Currency.Country() + Seperator;
    UserRecord += Currency.CurrencyCode() + Seperator;
    UserRecord += Currency.CurrencyName() + Seperator;
    UserRecord += to_string(Currency.Rate());

    return UserRecord;
  }

  static vector<clsCurrency> _LoadCurrencyDataFromFile() {
    vector<clsCurrency> vUsers;
    fstream MyFile;

    MyFile.open(CurrencyFileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;

      while (getline(MyFile, Line)) {
        clsCurrency Client = _ConvertLineToCurrencyObject(Line);
        vUsers.push_back(Client);
      }

      MyFile.close();
    }

    return vUsers;
  }

  void _Update() {
    vector<clsCurrency> _vCurrency;
    _vCurrency = _LoadCurrencyDataFromFile();

    for (clsCurrency &C : _vCurrency) {
      if (C.CurrencyCode() == CurrencyCode()) {
        C = *this;
        break;
      }
    }

    _SaveCurrencyDataToFile(_vCurrency);
  }

  static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrency) {
    fstream MyFile;

    MyFile.open(CurrencyFileName, ios::out); // overwrite
    string DataLine;

    if (MyFile.is_open()) {
      for (clsCurrency C : vCurrency) {
        DataLine = _ConvertCurrencyObjectToLine(C);
        MyFile << DataLine << endl;
      }

      MyFile.close();
    }
  }

  static clsCurrency _GetEmptyCurrencyObject() {
    return clsCurrency(enMode::enEmptyMode, "", "", "", 0);
  }

public:
  clsCurrency(enMode mode, string country, string currencycode,
              string currencyname, float rate) {
    _Mode = mode;
    _Country = country;
    _CurrencyCode = currencycode;
    _CurrencyName = currencyname;
    _Rate = rate;
  }

  bool IsEmpty() { return (_Mode == enMode::enEmptyMode); }

  string Country() { return _Country; }

  string CurrencyName() { return _CurrencyName; }

  string CurrencyCode() { return _CurrencyCode; }

  void UpdateRate(float NewRate) {
    _Rate = NewRate;
    _Update();
  }

  float Rate() { return _Rate; }

  static clsCurrency FindByCode(string CurrencyCode) {
    // make the currency code upper case.
    CurrencyCode = clsString::UpperAllString(CurrencyCode);
    fstream MyFile;

    MyFile.open(CurrencyFileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;

      while (getline(MyFile, Line)) {
        clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

        if (Currency.CurrencyCode() == CurrencyCode) {
          MyFile.close();
          return Currency;
        }
      }

      MyFile.close();
    }

    return _GetEmptyCurrencyObject();
  }

  static clsCurrency FindByCountry(string Country) {
    fstream MyFile;

    MyFile.open(CurrencyFileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;

      while (getline(MyFile, Line)) {
        clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

        // whatever the funk you enter, all is converted to upper.
        if (clsString::UpperAllString(Currency.Country()) ==
            clsString::UpperAllString(Country)) {
          MyFile.close();
          return Currency;
        }
      }

      MyFile.close();
    }

    return _GetEmptyCurrencyObject();
  }

  static bool IsCurrencyExist(string CurrencyCode) {
    clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
    return (!C1.IsEmpty());
  }

  static vector<clsCurrency> GetCurrencyList() {
    return _LoadCurrencyDataFromFile();
  }

  float ConvertToUSD(float amount) { return float(amount / Rate()); }

  float ConvertToOtherCurrency(float amount, clsCurrency currency2) {
    float AmountInUSD = ConvertToUSD(amount);

    if (currency2.CurrencyCode() == "USD") {
      return AmountInUSD;
    }

    return float(AmountInUSD * currency2.Rate());
  }
};
