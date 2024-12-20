#pragma once
#include "Global.h"
#include "Header Files/clsInputValidate.h"
#include "clsAddNewClient.h"
#include "clsClientsListScreen.h"
#include "clsDeleteClient.h"
#include "clsFindClientScreen.h"
#include "clsLoginRegister.h"
#include "clsLoginScreen.h"
#include "clsMainCurrency.h"
#include "clsMainUsers.h"
#include "clsScreen.h"
#include "clsTransactionScreen.h"
#include "clsUpdateClient.h"

class clsMainScreen : protected clsScreen {
private:
  enum enMainMenueOptions {
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenue = 6,
    eManageUsers = 7,
    eLoginRegister = 8,
    eCurrExch = 9,
    eExit = 10
  };

  static short _ReadMainMenueOption() {
    short N = 10;

    cout << "Choose what do you want to do [01 ~ " << N << "]: ";
    short Choice = clsInputValidate::ReadIntNumberBetween(
        1, N, "Enter number between [01 ~ 10]: ");

    return Choice;
  }

  static void _GoBackToMainMenue() {
    cout << "\n\nPress any key to go back to Main Menu...";

    int c = cin.get();
    cin.get();

    ShowMainMenue();
  }

  static void _ShowAllClientsScreen() {
    clsClientListScreen::ShowClientListScreen();
  }

  static void _ShowAddNewClientsScreen() {
    clsAddNewClient::ShowAddNewClientScreen();
  }

  static void _ShowDeleteClientScreen() {
    clsDeleteClient::ShowDeleteClientScreen();
  }

  static void _ShowUpdateClientScreen() {
    clsUpdateClient::ShowUpdateClientScreen();
  }

  static void _ShowFindClientScreen() {
    clsFindClientScreen::ShowFindClientScreen();
  }

  static void _ShowTransactionsMenue() {
    clsTransactionsScreen::ShowTransactionsMenu();
  }

  static void _ShowManageUsersMenue() {
    clsMainUsersScreen::ShowManageUsersMenue();
  }

  static void _ShowLoginRigsterScreen() {
    clsLoginRegisterScreen::ShowLoginRegisterScreen();
  }

  static void _CurrencyExchange() { clsMainCurrencyScreen::ShowCurrencyMenu(); }

  static void _LogOut() { CurrentUser = clsUser::Find("", ""); }

  static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
    switch (MainMenueOption) {
    case enMainMenueOptions::eListClients: {
      _ClearScreen();
      _ShowAllClientsScreen();
      _GoBackToMainMenue();
      break;
    }
    case enMainMenueOptions::eAddNewClient:
      /*system("clear");*/
      _ClearScreen();
      _ShowAddNewClientsScreen();
      _GoBackToMainMenue();
      break;

    case enMainMenueOptions::eDeleteClient:
      _ClearScreen();
      _ShowDeleteClientScreen();
      _GoBackToMainMenue();
      break;

    case enMainMenueOptions::eUpdateClient:
      _ClearScreen();
      _ShowUpdateClientScreen();
      _GoBackToMainMenue();
      break;

    case enMainMenueOptions::eFindClient:
      _ClearScreen();
      _ShowFindClientScreen();
      _GoBackToMainMenue();
      break;

    case enMainMenueOptions::eShowTransactionsMenue:
      _ClearScreen();
      _ShowTransactionsMenue();
      /*_GoBackToMainMenue();*/
      ShowMainMenue();
      break;

    case enMainMenueOptions::eManageUsers:
      _ClearScreen();
      _ShowManageUsersMenue();
      /*_GoBackToMainMenue();*/
      ShowMainMenue();
      break;
    case enMainMenueOptions::eLoginRegister:
      _ClearScreen();
      _ShowLoginRigsterScreen();
      _GoBackToMainMenue();
      break;

    case enMainMenueOptions::eCurrExch:
      _ClearScreen();
      _CurrencyExchange();
      _GoBackToMainMenue();

      break;

    case enMainMenueOptions::eExit:
      _ClearScreen();
      _LogOut();

      break;
    }
  }

public:
  static void ShowMainMenue() {
    _ClearScreen();
    _DrawScreenHeader("Main Screen");

    _Spret();
    cout << "\t[01] Show Client List.   ";
    clsScreen::PrintAccessEmoji(clsUser::enMainMenuePermissions::pListClients);

    cout << "\n\t[02] Add New Client.     ";
    clsScreen::PrintAccessEmoji(clsUser::enMainMenuePermissions::pAddNewClient);

    cout << "\n\t[03] Delete Client.      ";
    clsScreen::PrintAccessEmoji(clsUser::enMainMenuePermissions::pDeleteClient);

    cout << "\n\t[04] Update Client Info. ";
    clsScreen::PrintAccessEmoji(
        clsUser::enMainMenuePermissions::pUpdateClients);

    cout << "\n\t[05] Find Client.        ";
    clsScreen::PrintAccessEmoji(clsUser::enMainMenuePermissions::pFindClient);

    cout << "\n\t[06] Transactions.       ";
    clsScreen::PrintAccessEmoji(clsUser::enMainMenuePermissions::pTranactions);

    cout << "\n\t[07] Manage Users.       ";
    clsScreen::PrintAccessEmoji(clsUser::enMainMenuePermissions::pManageUsers);

    cout << "\n\t[08] Login Register      ";
    clsScreen::PrintAccessEmoji(clsUser::enMainMenuePermissions::pLoginScreen);

    cout << "\n\t[09] Currency Exchange   ";

    cout << "\n\t[10] Logout.             \n";
    _Spret();

    _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
  }
};
