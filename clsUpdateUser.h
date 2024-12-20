#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include <cctype>
#include <iomanip>

class clsUpdateUserScreen : protected clsScreen {
private:
  static void _ReadUserInfo(clsUser &Client) {
    cout << "\nEnter First Name: ";
    Client.FirstName = clsInputValidate::ReadString();

    cout << "\nEnter Last Name: ";
    Client.LastName = clsInputValidate::ReadString();

    cout << "\nEnter Email: ";
    Client.Email = clsInputValidate::ReadString();

    cout << "\nEnter Phone: ";
    Client.Phone = clsInputValidate::ReadString();

    cout << "\nEnter Password: ";
    Client.Password = clsInputValidate::ReadString();

    cout << "\nEnter Permissions: ";
    Client.Permissions = _ReadPermissionsToSet();
  }

  static int _ReadPermissionsToSet() {

    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      return -1;
    }

    cout << "\nDo you want to give access to:\n";

    cout << "\nShow Client List? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {

      Permissions += clsUser::enMainMenuePermissions::pListClients;
    }

    cout << "\nAdd New Client? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      Permissions += clsUser::enMainMenuePermissions::pAddNewClient;
    }

    cout << "\nDelete Client? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      Permissions += clsUser::enMainMenuePermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      Permissions += clsUser::enMainMenuePermissions::pUpdateClients;
    }

    cout << "\nFind Client? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      Permissions += clsUser::enMainMenuePermissions::pFindClient;
    }

    cout << "\nTransactions? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      Permissions += clsUser::enMainMenuePermissions::pTranactions;
    }

    cout << "\nManage Users? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      Permissions += clsUser::enMainMenuePermissions::pManageUsers;
    }

    cout << "\nShow login Register? [y/n]: ";
    cin >> Answer;
    if (tolower(Answer) == 'y') {
      Permissions += clsUser::enMainMenuePermissions::pLoginScreen;
    }

    return Permissions;
  }

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
  static void ShowUpdateUserScreen() {
    char Answer = 'n';

    _DrawScreenHeader("Update User Screen");

    cout << "\nPlease enter user name: ";
    string UserName = clsInputValidate::ReadString();

    while (!clsUser::IsUserExist(UserName)) {
      cout << "\nUser with name: " << UserName
           << " is not found! please try again: ";
      UserName = clsInputValidate::ReadString();
    }

    clsUser user1 = clsUser::Find(UserName);
    _PrintUser(user1);

    cout << "\nAre you sure you want to update this user? [y/n]: ";
    cin >> Answer;

    if (tolower(Answer) == 'y') {
      _ReadUserInfo(user1);
      clsUser::enSaveResults SaveResults;
      SaveResults = user1.Save();

      switch (SaveResults) {
      case clsUser::enSaveResults::svSucceeded: {
        cout << "\nUser updated successfully :)";
        _PrintUser(user1);
        break;
      }
      case clsUser::enSaveResults::svFaildEmptyOBject: {
        cout << "\nERROR, User was not updated because it's empty.";
        break;
      }
      }
    }
  }
};
