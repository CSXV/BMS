#pragma once
#include "clsBank.h"
#include "clsScreen.h"
#include <iomanip>
#include <string>

class clsTransferLog : protected clsScreen {
private:
  static void _PrintUserRecordLine(clsBankClient::stTransferLogRec User) {
    cout << "┃ " << setw(25) << left << User.DateTime;
    cout << "┃ " << setw(8) << left << User.SAcc;
    cout << "┃ " << setw(8) << left << User.DAcc;
    cout << "┃ " << setw(8) << left << User.Amount;
    cout << "┃ " << setw(10) << left << User.SBalance;
    cout << "┃ " << setw(10) << left << User.DBalance;
    cout << "┃ " << setw(8) << left << User.User << " ┃";
  }

public:
  static void ShowTransferLogScreen() {
    vector<clsBankClient::stTransferLogRec> vLoginRegisterRecord =
        clsBankClient::GetTransferfLog();

    string Title = "Transfer Log List Screen";
    string SubTitle =
        "(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

    _DrawScreenHeader(Title, SubTitle);

    if (vLoginRegisterRecord.size() == 0) {
      cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
      cout << "┃ No Transfer Logs Available In The System! ┃\n";
      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    } else {

      cout << "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━"
              "━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━┓\n";

      cout << "┃ " << left << setw(25) << "Date     - Time";
      cout << "┃ " << left << setw(8) << "S.Acc";
      cout << "┃ " << left << setw(8) << "D.Acc";
      cout << "┃ " << left << setw(8) << "Amount";
      cout << "┃ " << left << setw(10) << "S.Balance";
      cout << "┃ " << left << setw(10) << "D.Balance";
      cout << "┃ " << left << setw(8) << "User" << " ┃";

      cout << "\n┣━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━╋━━━━"
              "━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━┫\n";

      for (clsBankClient::stTransferLogRec Record : vLoginRegisterRecord) {
        _PrintUserRecordLine(Record);
        cout << endl;
      }

      cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━"
              "━━━━━━━┻━━━━━━━━━━━┻━━━━━━━━━━┛";
    }
  }
};
