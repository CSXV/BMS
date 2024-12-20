#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsAddNewUser.h"
#include "clsDeleteUser.h"
#include "clsFindUser.h"
#include "clsScreen.h"
#include "clsUpdateUser.h"
#include "clsUser.h"
#include "clsUserListScreen.h"

class clsMainUsersScreen : protected clsScreen {
private:
  enum enManageUsersMenueOptions {
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenue = 6
  };

  static short _ReadManageUsersMenueOption() {
    // just edit two numbers, N & the damn choice func.
    short N = 6;

    cout << "Choose what do you want to do [01 ~ 0" << N << "]: ";
    short Choice = clsInputValidate::ReadIntNumberBetween(
        1, N, "Enter number between [01 ~ 06]: ");

    return Choice;
  }

  static void _GoBackToManageUsersMenue() {
    cout << "\n\nPress any key to go back to Users Menu...";

    int c = cin.get();
    cin.get();

    ShowManageUsersMenue();
  }

  static void _ShowListUsersScreen() {
    clsUserListScreen::ShowAllUsersScreen();
  }

  static void _ShowAddNewUserScreen() {
    clsAddNewUserScreen::ShowAddNewUserScreen();
  }

  static void _ShowDeleteUserScreen() {
    clsDeleteUserScreen::ShowDeleteUserScreen();
  }

  static void _ShowUpdateUserScreen() {
    clsUpdateUserScreen::ShowUpdateUserScreen();
  }

  static void _ShowFindUserScreen() { clsFindUserScreen::ShowFindUserScreen(); }

  static void _PerfromManageUsersMenueOption(
      enManageUsersMenueOptions ManageUsersMenueOption) {
    switch (ManageUsersMenueOption) {
    case enManageUsersMenueOptions::eListUsers: {
      _ClearScreen();
      _ShowListUsersScreen();
      _GoBackToManageUsersMenue();
      break;
    }

    case enManageUsersMenueOptions::eAddNewUser: {
      _ClearScreen();
      _ShowAddNewUserScreen();
      _GoBackToManageUsersMenue();
      break;
    }

    case enManageUsersMenueOptions::eDeleteUser: {
      _ClearScreen();
      _ShowDeleteUserScreen();
      _GoBackToManageUsersMenue();
      break;
    }

    case enManageUsersMenueOptions::eUpdateUser: {
      _ClearScreen();
      _ShowUpdateUserScreen();
      _GoBackToManageUsersMenue();
      break;
    }

    case enManageUsersMenueOptions::eFindUser: {
      _ClearScreen();
      _ShowFindUserScreen();
      _GoBackToManageUsersMenue();
      break;
    }

    case enManageUsersMenueOptions::eMainMenue: {
      // Nothing here.
    }
    }
  }

public:
  static void ShowManageUsersMenue() {
    if (!CheckAccessRights(clsUser::enMainMenuePermissions::pManageUsers)) {
      return;
    }

    _ClearScreen();
    _DrawScreenHeader("Manage Users");

    _Spret();
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    _Spret();

    _PerfromManageUsersMenueOption(
        (enManageUsersMenueOptions)_ReadManageUsersMenueOption());
  }
};
