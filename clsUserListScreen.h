#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsUserListScreen : protected clsScreen {
private:
  static void _PrintUserRecordLine(clsUser User) {
    cout << "┃ " << setw(25) << left << User.FullName();
    cout << "┃ " << setw(12) << left << User.Phone;
    cout << "┃ " << setw(30) << left << User.Email;
    cout << "┃ " << setw(10) << left << User.Password;
    cout << "┃ " << setw(12) << left << User.Permissions << " ┃";
  }

public:
  static void ShowAllUsersScreen() {

    vector<clsUser> vUsers = clsUser::GetUserList();

    string Title = "Users List Screen.";
    string SubTitle = "[" + to_string(vUsers.size()) + "] User(s).";

    _DrawScreenHeader(Title, SubTitle);
    if (vUsers.size() == 0) {
      cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
      cout << "┃ No Users Available In the System! ┃\n";
      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    } else {

      cout << "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━━━━━┓\n";

      cout << "┃ " << left << setw(25) << "Full Name";
      cout << "┃ " << left << setw(12) << "Phone";
      cout << "┃ " << left << setw(30) << "Email";
      cout << "┃ " << left << setw(10) << "Password";
      cout << "┃ " << left << setw(12) << "Permissions" << " ┃";

      cout << "\n┣━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━━━━┫\n";

      for (clsUser User : vUsers) {
        _PrintUserRecordLine(User);
        cout << endl;
      }

      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━"
              "━━━━━━━━━┻━━━━━━━━━━━┻━━━━━━━━━━━━━━┛";
    }
  }
};
