#pragma once
#include "clsCurrency.h"
#include "clsScreen.h"
#include <iomanip>

class clsCurrenciesListScreen : protected clsScreen {
private:
  static void _PrintUserRecordLine(clsCurrency User) {
    cout << "┃ " << setw(28) << left << User.Country();
    cout << "┃ " << setw(7) << left << User.CurrencyCode();
    cout << "┃ " << setw(30) << left << User.CurrencyName();
    cout << "┃ " << setw(12) << left << User.Rate() << " ┃";
  }

public:
  static void ShowAllCurrenciesScreen() {
    vector<clsCurrency> vCurrency = clsCurrency::GetCurrencyList();

    string Title = "Currencies List Screen.";
    string SubTitle = "[" + to_string(vCurrency.size()) + "] Currencies.";

    _DrawScreenHeader(Title, SubTitle);

    if (vCurrency.size() == 0) {
      cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
      cout << "┃ No Currencies Available In the System! ┃\n";
      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    } else {

      cout << "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━┳━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┓\n";

      cout << "┃ " << left << setw(28) << "Country";
      cout << "┃ " << left << setw(7) << "Code";
      cout << "┃ " << left << setw(30) << "Name";
      cout << "┃ " << left << setw(12) << "Rate/(01$)" << " ┃";

      cout << "\n┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━╋━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━┫\n";

      for (clsCurrency Currency : vCurrency) {
        _PrintUserRecordLine(Currency);
        cout << endl;
      }

      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━┻━━━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━━━━┻━━━━━━━━━━━━━━┛";
    }
  }
};
