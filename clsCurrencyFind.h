#pragma once
#include "Header Files/clsInputValidate.h"
#include "Header Files/clsString.h"
#include "clsCurrency.h"
#include "clsScreen.h"
#include <iomanip>

class clsCurrencyFindScreen : protected clsScreen {
private:
  static void _PrintUser(clsCurrency Client) {
    cout << "\n┏━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┓";
    cout << "\n┃ Country    ┃ " << left << setw(23) << Client.Country() << "┃";
    cout << "\n┃ Code       ┃ " << left << setw(23) << Client.CurrencyCode()
         << "┃";
    cout << "\n┃ Name       ┃ " << left << setw(23) << Client.CurrencyName()
         << "┃";
    cout << "\n┃ Rate/(01$) ┃ " << left << setw(23) << Client.Rate() << "┃";
    cout << "\n┗━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━┛";
  }

  static clsCurrency _FindByCode() {
    cout << "\nPlease enter Currency code: ";

    string CurrencyCode = clsInputValidate::ReadString();

    while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

      cout << "\nCurrency with Code: " << CurrencyCode
           << " is not found! please try again: ";

      CurrencyCode = clsInputValidate::ReadString();
    }

    clsCurrency C1 =
        clsCurrency::FindByCode(clsString::UpperAllString(CurrencyCode));

    return C1;
  }

  static clsCurrency _FindByCountry() {
    cout << "\nPlease enter Country Name: ";

    string CountryName = clsInputValidate::ReadString();

    while (clsCurrency::FindByCountry(CountryName).IsEmpty()) {

      cout << "\nCountry with name: " << CountryName
           << " is not found! please try again: ";

      CountryName = clsInputValidate::ReadString();
    }

    clsCurrency C1 = clsCurrency::FindByCountry(CountryName);
    return C1;
  }

  static void _Make(clsCurrency C1) {
    if (!C1.IsEmpty()) {
      _PrintUser(C1);
    } else {
      cout << "\nCurrency was not found :(\n";
    }
  }

public:
  enum enAnswer { enCode = 1, enCountry = 2 };

  static void ShowFindCurrencyScreen() {
    _DrawScreenHeader("Find Currency Screen");

    cout << "\nFind by: [1] Code, or [2] Country? ";
    short Ans = clsInputValidate::ReadIntNumberBetween(1, 2);

    switch (Ans) {
    case enAnswer::enCode:
      _FindByCode();
      _Make(_FindByCode());
      break;
    case enAnswer::enCountry:
      _Make(_FindByCountry());
      break;
    }
  }
};
