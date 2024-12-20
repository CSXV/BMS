#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsCurrenciesList.h"
#include "clsCurrencyCalculator.h"
#include "clsCurrencyFind.h"
#include "clsCurrencyUpdate.h"
#include "clsScreen.h"
#include <iostream>
using namespace std;

class clsMainCurrencyScreen : protected clsScreen {
private:
  enum enCurrencyMenueOptions {
    eList = 1,
    eFind = 2,
    eUpdate = 3,
    eCalculator = 4,
    eMainMenue = 5
  };

  static short _ReadCurrencyMenuOptions() {
    // just edit two numbers, N & the damn choice func.
    short N = 5;

    cout << "Choose what do you want to do [01 ~ 0" << N << "]: ";
    short Choice = clsInputValidate::ReadIntNumberBetween(
        1, N, "Enter number between [01 ~ 05]: ");

    return Choice;
  }

  static void _GoBackToCurrencyMenu() {
    cout << "\n\nPress any key to go back to Currencies Menu...";

    int c = cin.get();
    cin.get();

    ShowCurrencyMenu();
  }

  static void _ShowListCurrencyScreen() {
    clsCurrenciesListScreen::ShowAllCurrenciesScreen();
  }

  static void _ShowFindScreen() {
    clsCurrencyFindScreen::ShowFindCurrencyScreen();
  }

  static void _ShowUpdateScreen() {
    clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
  }

  static void _ShowCalculatorScreen() {
    clsCurrencyClaculator::ShowCurrencyCalculatorScreen();
  }

  static void _PerfromManageUsersMenueOption(
      enCurrencyMenueOptions ManageUsersMenueOption) {
    switch (ManageUsersMenueOption) {
    case enCurrencyMenueOptions::eList: {
      _ClearScreen();
      _ShowListCurrencyScreen();
      _GoBackToCurrencyMenu();
      break;
    }

    case enCurrencyMenueOptions::eFind: {
      _ClearScreen();
      _ShowFindScreen();
      _GoBackToCurrencyMenu();
      break;
    }

    case enCurrencyMenueOptions::eUpdate: {
      _ClearScreen();
      _ShowUpdateScreen();
      _GoBackToCurrencyMenu();
      break;
    }

    case enCurrencyMenueOptions::eCalculator: {
      _ClearScreen();
      _ShowCalculatorScreen();
      _GoBackToCurrencyMenu();
      break;
    }

    case enCurrencyMenueOptions::eMainMenue: {
      // Nothing here.
    }
    }
  }

public:
  static void ShowCurrencyMenu() {
    if (!CheckAccessRights(clsUser::enMainMenuePermissions::pManageUsers)) {
      return;
    }

    _ClearScreen();
    _DrawScreenHeader("Currency Exchange Menu");

    _Spret();
    cout << "\t[1] List Currencies.\n";
    cout << "\t[2] Find Currency.\n";
    cout << "\t[3] Update Currency.\n";
    cout << "\t[4] Currency Calculator.\n";
    cout << "\t[5] Main Menu.\n";
    _Spret();

    _PerfromManageUsersMenueOption(
        (enCurrencyMenueOptions)_ReadCurrencyMenuOptions());
  }
};
