#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsCurrency.h"
#include "clsScreen.h"
#include <cctype>
#include <iomanip>

class clsUpdateCurrencyScreen : protected clsScreen {
private:
  static float _ReadRate() {
    cout << "\nEnter New Rate: ";
    float S = clsInputValidate::ReadFloatNumber();
    return S;
  }

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

public:
  static void ShowUpdateCurrencyScreen() {
    char Answer = 'n';

    _DrawScreenHeader("Update Currency Screen");

    cout << "\nPlease enter Currency code: ";
    string CurrencyCode = clsInputValidate::ReadString();

    while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
      cout << "\nCurrency with code: " << CurrencyCode
           << " is not found! please try again: ";
      CurrencyCode = clsInputValidate::ReadString();
    }

    clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
    _PrintUser(C1);

    cout << "\nAre you sure you want to update this Currency? [y/n]: ";
    cin >> Answer;

    if (tolower(Answer) == 'y') {
      C1.UpdateRate(_ReadRate());
      cout << "\nCurrency updated successfully :)";
      _PrintUser(C1);
    }
  }
};
