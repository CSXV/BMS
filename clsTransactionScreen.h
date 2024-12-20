#pragma once
#include "Header Files/clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsScreen.h"
#include "clsShowTotalBalancesScreen.h"
#include "clsTransferLogScreen.h"
#include "clsTransferScreen.h"
#include "clsWithdrawScreen.h"

class clsTransactionsScreen : protected clsScreen {
private:
  enum enTransactionsMenueOptions {
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eShowTransfer = 4,
    eShowTransferLog = 5,
    eShowMainMenue = 6
  };

  static short _ReadTransactionsMenueOption() {
    // just edit two numbers, N & the damn choice func.
    short N = 6;

    cout << "Choose what do you want to do [01 ~ 0" << N << "]: ";
    short Choice = clsInputValidate::ReadIntNumberBetween(
        1, N, "Enter number between [01 ~ 06]: ");

    return Choice;
  }

  static void _GoBackToTransactionsMenue() {
    cout << "\n\nPress any key to go back to Transaction Menu...";

    int c = cin.get();
    cin.get();

    ShowTransactionsMenu();
  }

  static void _ShowDepositScreen() { clsDepositScreen::ShowDepositScreen(); }

  static void _ShowWithDrawScreen() { clsWithDrawSreen::ShowWithDrawScreen(); }

  static void _ShowTotalBalancesScreen() {
    clsShowTotalBalancesScreen::ShowTotalBalances();
  }

  static void _ShowTransferScreen() { clsTransferScreen::ShowTransferScreen(); }

  static void _ShowTransferLogScreen() {
    clsTransferLog::ShowTransferLogScreen();
  }

  static void _PerfromTranactionsMenueOption(
      enTransactionsMenueOptions TransactionMenueOption) {

    switch (TransactionMenueOption) {
    case enTransactionsMenueOptions::eDeposit: {
      _ClearScreen();
      _ShowDepositScreen();
      _GoBackToTransactionsMenue();
      break;
    }

    case enTransactionsMenueOptions::eWithdraw: {
      _ClearScreen();
      _ShowWithDrawScreen();
      _GoBackToTransactionsMenue();
      break;
    }

    case enTransactionsMenueOptions::eShowTotalBalance: {
      _ClearScreen();
      _ShowTotalBalancesScreen();
      _GoBackToTransactionsMenue();
      break;
    }

    case enTransactionsMenueOptions::eShowTransfer: {
      _ClearScreen();
      _ShowTransferScreen();
      _GoBackToTransactionsMenue();
      break;
    }

    case enTransactionsMenueOptions::eShowTransferLog: {
      _ClearScreen();
      _ShowTransferLogScreen();
      _GoBackToTransactionsMenue();
      break;
    }

    case enTransactionsMenueOptions::eShowMainMenue: {
      // Do Nothing.
    }
    }
  }

public:
  static void ShowTransactionsMenu() {
    if (!CheckAccessRights(clsUser::enMainMenuePermissions::pTranactions)) {
      return;
    }

    _ClearScreen();
    _DrawScreenHeader("Transaction Screen");

    _Spret();
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Transfer.\n";
    cout << "\t[5] Transfer Log.\n";
    cout << "\t[6] Main Menu.\n";
    _Spret();

    _PerfromTranactionsMenueOption(
        (enTransactionsMenueOptions)_ReadTransactionsMenueOption());
  }
};
