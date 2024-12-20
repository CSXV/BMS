#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsDeleteUserScreen : protected clsScreen {
private:
  static void _PrintUser(clsUser Client) {
    cout << "\n┏━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┓";
    cout << "\n┃ First Name  ┃ " << left << setw(23) << Client.FirstName << "┃";
    cout << "\n┃ Last Name   ┃ " << left << setw(23) << Client.LastName << "┃";
    cout << "\n┃ Full Name   ┃ " << left << setw(23) << Client.FullName()
         << "┃";
    cout << "\n┃ Email       ┃ " << left << setw(23) << Client.Email << "┃";
    cout << "\n┃ Phone       ┃ " << left << setw(23) << Client.Phone << "┃";
    cout << "\n┃ User Name   ┃ " << left << setw(23) << Client.UserName << "┃";
    cout << "\n┃ Password    ┃ " << left << setw(23) << Client.Password << "┃";
    cout << "\n┃ Permissions ┃ " << left << setw(23) << Client.Permissions
         << "┃";
    cout << "\n┗━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━┛";
  }

public:
  static void ShowDeleteUserScreen() {
    char answer = 'y';

    _DrawScreenHeader("Delete User Screen");

    cout << "\nPlease enter user name: ";
    string UserName = clsInputValidate::ReadString();

    while (!clsUser::IsUserExist(UserName)) {
      cout << "\nUser with name: " << UserName
           << " is not found! please try again: ";
      UserName = clsInputValidate::ReadString();
    }

    clsUser user1 = clsUser::Find(UserName);
    _PrintUser(user1);

    cout << "\nAre you sure you want to delete this user? [y/n]: ";
    cin >> answer;

    if (tolower(answer) == 'y') {
      if (user1.Delete()) {
        cout << "\nUser deleted successfully.";
      } else {
        cout << "\nERROR, user was not deleted.";
      }
    }
  }
};
