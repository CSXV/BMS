#pragma once
#include "Global.h"
#include "Header Files/clsDate.h"
#include "clsUser.h"
#include <iomanip>
#include <iostream>
using namespace std;

class clsScreen {
protected:
  static void _ClearScreen() { system("clear"); }

  static void _Spret() {
    cout << "▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂\n";
  }

  static void _DrawScreenHeader(string Title, string SubTitle = "") {
    short Width = Title.length() + 11;

    cout << "\t┏";
    for (short i = 0; i < Width + 1; i++) {
      cout << "━";
    }
    cout << "┓";

    cout << "\n\t┃ " << left << setw(Width) << Title << "┃";
    if (SubTitle != "") {
      cout << "\n\t┃ " << left << setw(Width) << SubTitle << "┃";
    }

    cout << "\n\t┗";
    for (short i = 0; i < Width + 1; i++) {
      cout << "━";
    }
    cout << "┛\n";

    PrintHeader();
  }

  static bool CheckAccessRights(clsUser::enMainMenuePermissions Permission) {
    if (!CurrentUser.CheckAccessPermission(Permission)) {
      _DrawScreenHeader("ACCESS DENIED! Contact your Admin.");
      return false;
    } else {
      return true;
    }
  }

  static bool PrintAccessEmoji(clsUser::enMainMenuePermissions Permission) {
    string on = "✅ ";
    string off = "❌ ";

    if (CurrentUser.CheckAccessPermission(Permission)) {
      cout << on;
      return true;
    } else {
      cout << off;
      return false;
    }
  }

  static void PrintHeader() {
    // this prints Current user name.
    cout << "\tUser: " << CurrentUser.UserName << "\n";
    // this prints system date.
    cout << "\tDate: " << clsDate::DateToString(clsDate::GetSystemDate())
         << "\n\n";
  }
};
