#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsBank.h"
#include "clsScreen.h"
#include <iomanip>

class clsUpdateClient : protected clsScreen {
private:
  static void _ReadClientInfo(clsBankClient &Client) {
    cout << "\nEnter First Name: ";
    Client.FirstName = clsInputValidate::ReadString();

    cout << "\nEnter Last Name: ";
    Client.LastName = clsInputValidate::ReadString();

    cout << "\nEnter Email: ";
    Client.Email = clsInputValidate::ReadString();

    cout << "\nEnter Phone: ";
    Client.Phone = clsInputValidate::ReadString();

    cout << "\nEnter Pin Code: ";
    Client.PinCode = clsInputValidate::ReadString();

    cout << "\nEnter Account Balance: ";
    Client.AccountBalance = clsInputValidate::ReadFloatNumber();
  }

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
  static void ShowUpdateClientScreen() {
    if (!CheckAccessRights(clsUser::enMainMenuePermissions::pUpdateClients)) {
      return;
    }

    string AccountNumber = "";
    _DrawScreenHeader("Update Client Screen");

    cout << "\nPlease enter client account number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber)) {
      cout << "\nAccount Number" << AccountNumber
           << " is not found, please try again: ";
      AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient client1 = clsBankClient::Find(AccountNumber);
    _PrintClient(client1);

    _ReadClientInfo(client1);
    clsBankClient::enSaveResults SaveResults;
    SaveResults = client1.Save();

    switch (SaveResults) {
    case clsBankClient::enSaveResults::svSucceeded: {
      cout << "\nClient updated successfully :)";
      _PrintClient(client1);
      break;
    }
    case clsBankClient::enSaveResults::svFaildAccountNumberExists: {
      cout << "\nERROR, Client was not updated because it's already userd.";
      break;
    }
    case clsBankClient::enSaveResults::svFaildEmptyOBject: {
      cout << "\nERROR, Client was not updated because it's empty.";
      break;
    }
    }
  }
};
