#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen {
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

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
      return -1;
    }

    cout << "\nDo you want to give access to : \n ";

    cout << "\nShow Client List? [y/n]: ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {

      Permissions += clsUser::enMainMenuePermissions::pListClients;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
      Permissions += clsUser::enMainMenuePermissions::pAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
      Permissions += clsUser::enMainMenuePermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
      Permissions += clsUser::enMainMenuePermissions::pUpdateClients;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
      Permissions += clsUser::enMainMenuePermissions::pFindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
      Permissions += clsUser::enMainMenuePermissions::pTranactions;
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
      Permissions += clsUser::enMainMenuePermissions::pManageUsers;
    }

    cout << "\nShow login Register? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
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
  static void ShowAddNewUserScreen() {
    _DrawScreenHeader("Add New User Screen");

    cout << "\nPlease enter User Name: ";
    string UserName = clsInputValidate::ReadString();

    while (clsUser::IsUserExist(UserName)) {
      cout << "\nUser Name is already used! Choose another one: ";
      UserName = clsInputValidate::ReadString();
    }

    clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

    _ReadUserInfo(NewUser);
    clsUser::enSaveResults SaveResults;
    SaveResults = NewUser.Save();

    switch (SaveResults) {
    case clsUser::enSaveResults::svSucceeded: {
      cout << "\nUser Added successfully :)";
      _PrintUser(NewUser);
      break;
    }
    case clsUser::enSaveResults::svFaildEmptyOBject: {
      cout << "\nERROR, user was not saved because it's empty.";
      break;
    }
    case clsUser::enSaveResults::svFaildUserExists: {
      cout << "\nERROR, user was not saved because user name is already "
              "used.";
      break;
    }
    }
  }
};
