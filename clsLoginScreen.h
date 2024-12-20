#pragma once
#include "Global.h"
#include "Header Files/clsInputValidate.h"
#include "clsMain.h"
#include "clsScreen.h"

class clsLoginScreen : protected clsScreen {
private:
  static bool _login() {
    bool LoginFaild = false;
    short counter = 0;

    do {
      if (LoginFaild) {
        counter++;
        cout << "Invlaid Username/Password!\n";
        cout << "You have " << 3 - counter << " Trials to login\n";
      }

      if (counter == 3) {
        cout << "You are locked after 03 faild trials.\n";
        return false;
      }

      cout << "Enter Username: ";
      string Username = clsInputValidate::ReadString();

      cout << "Enter Password: ";
      string Password = clsInputValidate::ReadString();

      CurrentUser = clsUser::Find(Username, Password);
      LoginFaild = CurrentUser.IsEmpty();

    } while (LoginFaild);

    CurrentUser.RegisterLogin();
    clsMainScreen::ShowMainMenue();
    return true;
  }

public:
  static bool ShowLoginScreen() {
    _ClearScreen();
    _DrawScreenHeader("Login Screen");
    _Spret();

    return _login();
  }
};
