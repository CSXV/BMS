#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsBank.h"
#include "clsScreen.h"
#include <iomanip>

class clsFindClientScreen : protected clsScreen {
private:
  static void _PrintClient(clsBankClient Client) {
    cout << "\n┏━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┓";
    cout << "\n┃ First Name    ┃ " << left << setw(23) << Client.FirstName
         << "┃";
    cout << "\n┃ Last Name     ┃ " << left << setw(23) << Client.LastName
         << "┃";
    cout << "\n┃ Full Name     ┃ " << left << setw(23) << Client.FullName()
         << "┃";
    cout << "\n┃ Email         ┃ " << left << setw(23) << Client.Email << "┃";
    cout << "\n┃ Phone         ┃ " << left << setw(23) << Client.Phone << "┃";
    cout << "\n┃ Acc. Number   ┃ " << left << setw(23) << Client.AccountNumber()
         << "┃";
    cout << "\n┃ Password      ┃ " << left << setw(23) << Client.PinCode << "┃";
    cout << "\n┃ Balance       ┃ " << left << setw(23) << Client.AccountBalance
         << "┃";
    cout << "\n┗━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━┛";
  }

public:
  static void ShowFindClientScreen() {
    if (!CheckAccessRights(clsUser::enMainMenuePermissions::pFindClient)) {
      return;
    }

    string AccountNumber = "";
    _DrawScreenHeader("Find Client Screen");

    cout << "\nPlease enter client account number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber)) {
      cout << "\nAccount Number" << AccountNumber
           << " is not found, please try again: ";
      AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient client1 = clsBankClient::Find(AccountNumber);

    if (!client1.IsEmpty()) {
      _PrintClient(client1);
    } else {
      cout << "\nClient was not found :(\n";
    }
  }
};
