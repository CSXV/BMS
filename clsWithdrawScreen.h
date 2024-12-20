#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsBank.h"
#include "clsScreen.h"
#include <cctype>
#include <iomanip>

class clsWithDrawSreen : protected clsScreen {
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
  static void ShowWithDrawScreen() {
    string AccountNumber = "";
    char Answer = 'n';

    _DrawScreenHeader("WithDraw Screen");

    cout << "\nPlease enter client's account number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber)) {
      cout << "\nAccount Number" << AccountNumber
           << " is not found, please try again: ";
      AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient client1 = clsBankClient::Find(AccountNumber);
    _PrintClient(client1);

    double Amount = 0;
    cout << "\nPlease enter Withdraw amount: ";
    Amount = clsInputValidate::ReadIntNumber();

    cout << "\n\nAre you sure you want perfrom this transaction? [y/n]: ";
    cin >> Answer;

    if (tolower(Answer) == 'y') {
      if (client1.Withdraw(Amount)) {
        cout << "\nAmount Withdrawed successfully.";
        cout << "\nNew balance is: " << client1.AccountBalance;
      } else {
        cout << "\nCannot withdraw, insuffecient balance.";
        cout << "\nAmount to withdraw is: " << Amount;
        cout << "\nYour balance is: " << client1.AccountBalance;
      }
    } else {
      cout << "\nOperation was cancelled.";
    }
  }
};
