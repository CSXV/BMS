#pragma once
#include "Header Files/clsInputValidate.h"
#include "Header Files/clsString.h"
#include "clsCurrency.h"
#include "clsScreen.h"

class clsCurrencyClaculator : protected clsScreen {
private:
  static void _PrintUser(clsCurrency Client) {
    cout << "┏━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    cout << "\n┃ Country    ┃ " << left << setw(27) << Client.Country() << "┃";
    cout << "\n┃ Code       ┃ " << left << setw(27) << Client.CurrencyCode()
         << "┃";
    cout << "\n┃ Name       ┃ " << left << setw(27) << Client.CurrencyName()
         << "┃";
    cout << "\n┃ Rate/(01$) ┃ " << left << setw(27) << Client.Rate() << "┃";
    cout << "\n┗━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
  }

  static float _ReadAmount() {
    cout << "\n\nEnter anount to exchange: ";
    float A = clsInputValidate::ReadFloatNumber();

    return A;
  }

  static clsCurrency _GetCurrency(string message) {
    cout << message;
    string Currency1 = clsInputValidate::ReadString();
    clsString::UpperAllString(Currency1);

    while (!clsCurrency::IsCurrencyExist(Currency1)) {
      cout << "\nCurrency with code: " << Currency1
           << " is not found! please try again: ";
      Currency1 = clsInputValidate::ReadString();
    }

    clsCurrency C1 = clsCurrency::FindByCode(Currency1);

    _PrintUser(C1);

    return C1;
  }

  static void _PrintCalculationResults(float A, clsCurrency C1,
                                       clsCurrency C2) {
    cout << "\n"
         << A << " " << C1.CurrencyCode() << " = "
         << C1.ConvertToOtherCurrency(A, C2) << " " << C2.CurrencyCode()
         << "\n";
  }

public:
  static void ShowCurrencyCalculatorScreen() {
    char Answer = 'n';

    do {
      _ClearScreen();
      _DrawScreenHeader("Currency Claculator Screen");

      // Currency1
      clsCurrency C1 = _GetCurrency("Please enter Currency 01 code: ");
      // Currency2
      clsCurrency C2 = _GetCurrency("\n\nPlease enter Currency 02 code: ");
      // amount
      float A = _ReadAmount();

      _PrintCalculationResults(A, C1, C2);

      cout << "\nDo you want to perform another calculation? [y/n]: ";
      cin >> Answer;

    } while (Answer == 'y');
  }
};
