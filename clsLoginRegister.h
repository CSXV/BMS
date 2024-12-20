#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include <string>

class clsLoginRegisterScreen : protected clsScreen {
private:
  static void _PrintUserRecordLine(clsUser::stLoginRegisterRecord User) {
    cout << "┃ " << setw(25) << left << User.DateTime;
    cout << "┃ " << setw(15) << left << User.UserName;
    cout << "┃ " << setw(15) << left << User.Password;
    cout << "┃ " << setw(10) << left << User.Permissions << "  ┃";
  }

public:
  static void ShowLoginRegisterScreen() {
    if (!CheckAccessRights(clsUser::enMainMenuePermissions::pLoginScreen)) {
      return;
    }

    vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord =
        clsUser::GetLoginRegisterList();

    string Title = "Login Register List Screen.";
    string SubTitle =
        "[" + to_string(vLoginRegisterRecord.size()) + "] Record(s).";

    _DrawScreenHeader(Title, SubTitle);

    if (vLoginRegisterRecord.size() == 0) {
      cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
      cout << "┃ No Logins Logs Available In The System! ┃\n";
      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    } else {

      cout << "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳"
              "━━━━━━━━━━━━━┓\n";

      cout << "┃ " << left << setw(25) << "Date     - Time";
      cout << "┃ " << left << setw(15) << "UserName";
      cout << "┃ " << left << setw(15) << "Password";
      cout << "┃ " << left << setw(10) << "Permissions" << " ┃";

      cout << "\n┣━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋"
              "━━━━━━━━━━━━━┫\n";

      for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord) {
        _PrintUserRecordLine(Record);
        cout << endl;
      }

      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┻━━"
              "━━━━━━━━━━━┛";
    }
  }
};
