#pragma once
#include "Header Files/clsDate.h"
#include "Header Files/clsPerson.h"
#include "Header Files/clsString.h"
#include "Header Files/clsUtil.h"
#include <fstream>
#include <string>
using namespace std;

string const UsersFileName{"Users.txt"};
string const LogFileName{"LoginRegister.txt"};

class clsUser : public clsPerson {
public:
  struct stLoginRegisterRecord;

private:
  enum enMode { enEmptyMode = 0, enUpdateMode = 1, enAddNewMode = 2 };
  enMode _Mode;

  string _UserName;
  string _Password;
  int _Permissions;
  bool _MarkForDelete = false;

  static stLoginRegisterRecord
  _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#") {
    stLoginRegisterRecord LoginRegisterRecord;
    vector<string> LoginRegisterDataLine = clsString::Split(Line, Seperator);

    LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
    LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
    LoginRegisterRecord.Password =
        clsUtil::DecryptText(LoginRegisterDataLine[2]);
    LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

    return LoginRegisterRecord;
  }

  static clsUser _ConvertLinetoUserObject(string Line,
                                          string Seperator = "#//#") {
    vector<string> vClientData;
    vClientData = clsString::Split(Line, Seperator);

    return clsUser(enMode::enUpdateMode, vClientData[0], vClientData[1],
                   vClientData[2], vClientData[3], vClientData[4],
                   clsUtil::DecryptText(vClientData[5]), stod(vClientData[6]));
  }

  string _PrepareLogInRecord(string Seperator = "#//#") {
    string LoginRecord = "";

    LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
    LoginRecord += UserName + Seperator;
    LoginRecord += clsUtil::EncryptText(Password) + Seperator;
    LoginRecord += to_string(Permissions) + Seperator;

    return LoginRecord;
  }

  static string _ConvertUserObejctToLine(clsUser User,
                                         string Seperator = "#//#") {
    string UserRecord = "";

    UserRecord += User.FirstName + Seperator;
    UserRecord += User.LastName + Seperator;
    UserRecord += User.Email + Seperator;
    UserRecord += User.Phone + Seperator;
    UserRecord += User.UserName + Seperator;
    UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
    UserRecord += to_string(User.Permissions);

    return UserRecord;
  }

  static clsUser _GetEmptyUserObject() {
    return clsUser(enMode::enEmptyMode, "", "", "", "", "", "", 0);
  }

  static void _SaveUserDataToFile(vector<clsUser> vUsers) {
    fstream MyFile;

    MyFile.open(UsersFileName, ios::out); // overwrite
    string DataLine;

    if (MyFile.is_open()) {
      for (clsUser C : vUsers) {

        if (C._MarkForDelete == false) {
          // we only write records that are not marked for delete.
          DataLine = _ConvertUserObejctToLine(C);
          MyFile << DataLine << endl;
        }
      }

      MyFile.close();
    }
  }

  static vector<clsUser> _LoadUsersDataFromFile() {
    vector<clsUser> vUsers;
    fstream MyFile;

    MyFile.open(UsersFileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;

      while (getline(MyFile, Line)) {
        clsUser Client = _ConvertLinetoUserObject(Line);
        vUsers.push_back(Client);
      }

      MyFile.close();
    }

    return vUsers;
  }

  void _AddDataLineToFile(string stDataLine) {
    fstream MyFile;

    MyFile.open(UsersFileName, ios::out | ios::app); // overwrite

    if (MyFile.is_open()) {
      MyFile << stDataLine << endl;
      MyFile.close();
    }
  }

  void _AddNew() { _AddDataLineToFile(_ConvertUserObejctToLine(*this)); }

  void _Update() {
    vector<clsUser> _vUsers;
    _vUsers = _LoadUsersDataFromFile();

    for (clsUser &C : _vUsers) {
      if (C.UserName == UserName) {
        C = *this;
        break;
      }
    }

    _SaveUserDataToFile(_vUsers);
  }

public:
  enum enMainMenuePermissions {
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTranactions = 32,
    pManageUsers = 64,
    pLoginScreen = 128
  };

  enum enSaveResults {
    svFaildEmptyOBject = 0,
    svSucceeded = 1,
    svFaildUserExists = 2
  };

  struct stLoginRegisterRecord {
    string DateTime;
    string UserName;
    string Password;
    int Permissions;
  };

  clsUser(enMode Mode, string FirstName, string LastName, string Email,
          string Phone, string UserName, string Password, int Permissions)
      : clsPerson(FirstName, LastName, Email, Phone) {
    _Mode = Mode;
    _UserName = UserName;
    _Password = Password;
    _Permissions = Permissions;
  };

  bool IsEmpty() { return (_Mode == enMode::enEmptyMode); }

  bool MarkForDelete() { return _MarkForDelete; }

  void SetUserName(string UserName) { _UserName = UserName; }
  string GetUserName() { return _UserName; }
  __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

  void SetPassword(string Password) { _Password = Password; }
  string GetPassword() { return _Password; }
  __declspec(property(get = GetPassword, put = SetPassword)) string Password;

  void SetPermissions(int Permissions) { _Permissions = Permissions; }
  int GetPermissions() { return _Permissions; }
  __declspec(property(get = GetPermissions,
                      put = SetPermissions)) string Permissions;

  static clsUser Find(string UserName) {
    fstream MyFile;

    MyFile.open(UsersFileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;

      while (getline(MyFile, Line)) {
        clsUser Client = _ConvertLinetoUserObject(Line);

        if (Client.UserName == UserName) {
          MyFile.close();
          return Client;
        }
      }

      MyFile.close();
    }

    return _GetEmptyUserObject();
  }

  static clsUser Find(string UserName, string Password) {
    fstream MyFile;

    MyFile.open(UsersFileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;

      while (getline(MyFile, Line)) {
        clsUser Client = _ConvertLinetoUserObject(Line);

        if (Client.UserName == UserName && Client.Password == Password) {
          MyFile.close();
          return Client;
        }
      }

      MyFile.close();
    }

    return _GetEmptyUserObject();
  }

  static bool IsUserExist(string UserName) {
    clsUser User = clsUser::Find(UserName);
    return (!User.IsEmpty());
  }

  enSaveResults Save() {
    switch (_Mode) {
    case enMode::enEmptyMode: {
      if (IsEmpty()) {
        return enSaveResults::svFaildEmptyOBject;
      }
    }
    case enMode::enUpdateMode: {
      _Update();
      return enSaveResults::svSucceeded;
      break;
    }
    case enMode::enAddNewMode: {
      if (clsUser::IsUserExist(_UserName)) {
        return enSaveResults::svFaildUserExists;
      } else {
        _AddNew();
        _Mode = enMode::enUpdateMode;
        return enSaveResults::svSucceeded;
      }
      break;
    }
    }
  }

  bool Delete() {
    vector<clsUser> _vUser;
    _vUser = _LoadUsersDataFromFile();

    for (clsUser &U : _vUser) {
      if (U.UserName == _UserName) {
        U._MarkForDelete = true;
        break;
      }
    }

    _SaveUserDataToFile(_vUser);
    *this = _GetEmptyUserObject();

    return true;
  }

  static clsUser GetAddNewUserObject(string UserName) {
    return clsUser(enMode::enAddNewMode, "", "", "", "", UserName, "", 0);
  }

  static vector<clsUser> GetUserList() { return _LoadUsersDataFromFile(); }

  static vector<stLoginRegisterRecord> GetLoginRegisterList() {
    vector<stLoginRegisterRecord> vLoginRegisterRecord;
    fstream MyFile;

    MyFile.open("LoginRegister.txt", ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;

      stLoginRegisterRecord LoginRegisterRecord;

      while (getline(MyFile, Line)) {
        LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
        vLoginRegisterRecord.push_back(LoginRegisterRecord);
      }

      MyFile.close();
    }

    return vLoginRegisterRecord;
  }

  bool CheckAccessPermission(enMainMenuePermissions Permission) {
    if (this->Permissions == enMainMenuePermissions::eAll)
      return true;

    if ((Permission & this->Permissions) == Permission)
      return true;
    else
      return false;
  }

  void RegisterLogin() {
    string stDataLine = _PrepareLogInRecord();
    fstream MyFile;

    MyFile.open(LogFileName, ios::out | ios::app); // overwrite

    if (MyFile.is_open()) {
      MyFile << stDataLine << endl;
      MyFile.close();
    }
  }
};
