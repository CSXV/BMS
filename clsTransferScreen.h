#pragma once
#include "Global.h"
#include "Header Files/clsInputValidate.h"
#include "clsBank.h"
#include "clsScreen.h"
#include <cctype>

class clsTransferScreen : protected clsScreen {
private:
  static void _PrintClient(clsBankClient Client) {
    cout << "\n┏━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┓";
    cout << "\n┃ Full Name     ┃ " << left << setw(23) << Client.FullName()
         << "┃";
    cout << "\n┃ Acc. Number   ┃ " << left << setw(23) << Client.AccountNumber()
         << "┃";
    cout << "\n┃ Balance       ┃ " << left << setw(23) << Client.AccountBalance
         << "┃";
    cout << "\n┗━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━┛";
  }

  static string _ReadAccountNumber(string what) {
    string AccountNumber;

    cout << "\nPlease Enter Account Number to Transfer " << what << ": ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber)) {
      cout << "\nAccount Number" << AccountNumber
           << " is not found, please try again: ";
      AccountNumber = clsInputValidate::ReadString();
    }

    return AccountNumber;
  }

  static float ReadAmount(clsBankClient SourceClient) {
    float Amount;

    cout << "\nEnter Transfer Amount: ";
    Amount = clsInputValidate::ReadFloatNumber();

    while (Amount > SourceClient.AccountBalance) {
      cout << "\nAmount Exceeds the available Balance, Enter another Amount: ";
      Amount = clsInputValidate::ReadDblNumber();
    }

    return Amount;
  }

public:
  static void ShowTransferScreen() {
    char Answer = 'n';

    _DrawScreenHeader("Transfer Screen");

    clsBankClient SourceClient =
        clsBankClient::Find(_ReadAccountNumber("From"));
    _PrintClient(SourceClient);

    clsBankClient DestinationClient =
        clsBankClient::Find(_ReadAccountNumber("to"));
    _PrintClient(DestinationClient);

    float Amount = ReadAmount(SourceClient);

    cout << "\n\nAre you sure you want perfrom this operation? [y/n]: ";
    cin >> Answer;

    if (tolower(Answer) == 'y') {
      if (SourceClient.Transfer(Amount, DestinationClient,
                                CurrentUser.UserName)) {
        cout << "\nTransfer done successfully.";
      }
    } else {
      cout << "\nOperation was cancelled.";
    }

    _PrintClient(SourceClient);
    _PrintClient(DestinationClient);
  }
};
