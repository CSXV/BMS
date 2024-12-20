#pragma once
#include "Header Files/clsUtil.h"
#include "clsBank.h"
#include "clsScreen.h"
#include <iomanip>
#include <string>

class clsShowTotalBalancesScreen : protected clsScreen {
private:
  static void _PrintClientRecordBalanceLine(clsBankClient Client) {

    cout << "┃ " << setw(15) << left << Client.AccountNumber();
    cout << "┃ " << setw(40) << left << Client.FullName();
    cout << "┃ " << setw(12) << left << Client.AccountBalance << " ┃";
  }

public:
  static void ShowTotalBalances() {
    vector<clsBankClient> vClients = clsBankClient::GetClientsList();

    string Title = "Balances list screen.";
    string SubTitle = "[" + to_string(vClients.size()) + "] Client(s).";
    _DrawScreenHeader(Title, SubTitle);

    double TotalBalances = clsBankClient::GetTotalBalances();

    if (vClients.size() == 0) {
      cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
      cout << "┃ No Clients Available In the System! ┃\n";
      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    } else {

      cout << "\n┏━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━"
              "━━━━━━━━━━━━┓\n";

      cout << "┃ " << left << setw(15) << "Accout Number";
      cout << "┃ " << left << setw(40) << "Client Name";
      cout << "┃ " << left << setw(12) << "Balance" << " ┃";

      cout << "\n┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━"
              "━━━━━━━━━━━━┫\n";

      for (clsBankClient Client : vClients) {
        _PrintClientRecordBalanceLine(Client);
        cout << endl;
      }

      cout << "┣━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━"
              "━━━━━━━━━━┫";

      cout << "\n┃ " << "Total Balances = " << left << setw(54) << TotalBalances
           << " ┃";
      cout << "\n┃ " << "( " << clsUtil::NumberToText(TotalBalances) << left
           << setw(33) << ")" << " ┃";

      cout << "\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━━━━┛";
    }
  }
};
