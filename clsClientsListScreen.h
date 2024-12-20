#pragma once
#include "clsBank.h"
#include "clsScreen.h"
#include <iomanip>
#include <string>

class clsClientListScreen : protected clsScreen {
private:
  static void _PrintClientRecordLine(clsBankClient Client) {

    cout << "┃ " << setw(15) << left << Client.AccountNumber();
    cout << "┃ " << setw(10) << left << Client.PinCode;
    cout << "┃ " << setw(40) << left << Client.FullName();
    cout << "┃ " << setw(12) << left << Client.Phone;
    cout << "┃ " << setw(12) << left << Client.AccountBalance << " ┃";
  }

public:
  static void ShowClientListScreen() {
    if (!CheckAccessRights(clsUser::enMainMenuePermissions::pListClients)) {
      return;
    }

    vector<clsBankClient> vClients = clsBankClient::GetClientsList();

    string Title = "Client List Screen";
    string SubTitle = "[" + to_string(vClients.size()) + "] Client(s).";

    _DrawScreenHeader(Title, SubTitle);

    if (vClients.size() == 0) {
      cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
      cout << "┃ No Clients Available In the System! ┃\n";
      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    } else {

      cout << "\n┏━━━━━━━━━━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┓\n";

      cout << "┃ " << left << setw(15) << "Accout Number";
      cout << "┃ " << left << setw(10) << "Pin Code";
      cout << "┃ " << left << setw(40) << "Client Name";
      cout << "┃ " << left << setw(12) << "Phone";
      cout << "┃ " << left << setw(12) << "Balance" << " ┃";

      cout << "\n┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━┫\n";

      for (clsBankClient Client : vClients) {
        _PrintClientRecordLine(Client);
        cout << endl;
      }

      cout << "┗━━━━━━━━━━━━━━━━┻━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━┛";
    }
  }
};
