#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsBank.h"
#include "clsScreen.h"
#include <cctype>
#include <iomanip>

class clsDepositScreen : protected clsScreen {
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
  static void ShowDepositScreen() {
    string AccountNumber = "";
    char Answer = 'n';

    _DrawScreenHeader("Deposit Screen");

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
    cout << "\nPlease enter deposit amount: ";
    Amount = clsInputValidate::ReadIntNumber();

    cout << "\n\nAre you sure you want perfrom this transaction? [y/n]: ";
    cin >> Answer;

    if (tolower(Answer) == 'y') {
      client1.Deposit(Amount);
      cout << "\nAmount Deposited successfully.";
      cout << "\nNew balance is: " << client1.AccountBalance;
    } else {
      cout << "\nOperation was cancelled.";
    }
  }
};
