#pragma once
#include "Global.h"
#include "Header Files/clsDate.h"
#include "Header Files/clsPerson.h"
#include "Header Files/clsString.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string const FileName{"Clients.txt"};
string const TransferLogFile{"TransferLog.txt"};

class clsBankClient : public clsPerson {
public:
  struct stTransferLogRec;

private:
  enum enMode { enEmptyMode = 0, enUpdateMode = 1, enAddNewMode = 2 };
  enMode _Mode;

  string _AccountNumber;
  string _PinCode;
  float _AccountBalance;
  bool _MarkForDelete = false;

  static stTransferLogRec
  _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#") {

    stTransferLogRec TrnsferLogRecord;

    vector<string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
    TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
    TrnsferLogRecord.SAcc = vTrnsferLogRecordLine[1];
    TrnsferLogRecord.DAcc = vTrnsferLogRecordLine[2];
    TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
    TrnsferLogRecord.SBalance = stod(vTrnsferLogRecordLine[4]);
    TrnsferLogRecord.DBalance = stod(vTrnsferLogRecordLine[5]);
    TrnsferLogRecord.User = vTrnsferLogRecordLine[6];

    return TrnsferLogRecord;
  }

  void _RegisterTransferLog(clsBankClient DistClient, double amount,
                            string username) {
    string DataLine = _ConvertTransferLogToLine(DistClient, amount, username);

    fstream MyFile;

    MyFile.open(TransferLogFile, ios::out | ios::app); // overwrite

    if (MyFile.is_open()) {
      MyFile << DataLine << endl;

      MyFile.close();
    }
  }

  string _ConvertTransferLogToLine(clsBankClient Client, double amount,
                                   string username, string Seperator = "#//#") {
    string stClientRecord = "";

    stClientRecord += clsDate::GetSystemDateTimeString() + Seperator;
    stClientRecord += AccountNumber() + Seperator;
    stClientRecord += Client.AccountNumber() + Seperator;
    stClientRecord += to_string(amount) + Seperator;
    stClientRecord += to_string(AccountBalance) + Seperator;
    stClientRecord += to_string(Client.AccountBalance) + Seperator;
    stClientRecord += username;

    return stClientRecord;
  }

  static clsBankClient _ConvertLinetoClientObject(string Line,
                                                  string Seperator = "#//#") {
    vector<string> vClientData;
    vClientData = clsString::Split(Line, Seperator);

    return clsBankClient(enMode::enUpdateMode, vClientData[0], vClientData[1],
                         vClientData[2], vClientData[3], vClientData[4],
                         vClientData[5], stod(vClientData[6]));
  }

  static string _ConvertClientObejctToLine(clsBankClient Client,
                                           string Seperator = "#//#") {
    string stClientRecord = "";

    stClientRecord += Client.FirstName + Seperator;
    stClientRecord += Client.LastName + Seperator;
    stClientRecord += Client.Email + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += Client.AccountNumber() + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += to_string(Client._AccountBalance);

    return stClientRecord;
  }

  static clsBankClient _GetEmptyClientObject() {
    return clsBankClient(enMode::enEmptyMode, "", "", "", "", "", "", 0);
  }

  static void _SaveCleintsDataToFile(vector<clsBankClient> vClients) {

    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open()) {
      for (clsBankClient C : vClients) {
        if (C._MarkForDelete == false) {
          // we only write records that are not marked for delete.
          DataLine = _ConvertClientObejctToLine(C);
          MyFile << DataLine << endl;
        }
      }

      MyFile.close();
    }
  }

  static vector<clsBankClient> _LoadCleintsDataFromFile() {
    vector<clsBankClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;

      while (getline(MyFile, Line)) {
        clsBankClient Client = _ConvertLinetoClientObject(Line);
        vClients.push_back(Client);
      }

      MyFile.close();
    }

    return vClients;
  }

  void _Update() {
    vector<clsBankClient> _vClients;
    _vClients = _LoadCleintsDataFromFile();

    for (clsBankClient &C : _vClients) {
      if (C.AccountNumber() == AccountNumber()) {
        C = *this;
        break;
      }
    }
    _SaveCleintsDataToFile(_vClients);
  }

  void _AddDataLineToFile(string stDataLine) {
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app); // overwrite

    if (MyFile.is_open()) {
      MyFile << stDataLine << endl;
      MyFile.close();
    }
  }

  void _AddNew() { _AddDataLineToFile(_ConvertClientObejctToLine(*this)); }

public:
  struct stTransferLogRec {
    string DateTime;
    string SAcc;
    string DAcc;
    float Amount;
    float SBalance;
    float DBalance;
    string User;
  };

  clsBankClient(enMode Mode, string FirstName, string LastName, string Email,
                string Phone, string AccountNumber, string PinCode,
                float AccountBalance)
      : clsPerson(FirstName, LastName, Email, Phone) {
    _Mode = Mode;
    _AccountNumber = AccountNumber;
    _AccountBalance = AccountBalance;
    _PinCode = PinCode;
  }

  bool IsEmpty() { return (_Mode == enMode::enEmptyMode); }

  string AccountNumber() { return _AccountNumber; }

  void SetPinCode(string PinCode) { _PinCode = PinCode; }
  string GetPinCode() { return _PinCode; }
  __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

  void SetAccountBalance(float AccountBalance) {
    _AccountBalance = AccountBalance;
  }
  float GetAccountBalance() { return _AccountBalance; }
  __declspec(property(get = GetAccountBalance,
                      put = SetAccountBalance)) float AccountBalance;

  void Print() {
    cout << "\nClient Card:";
    cout << "\n__________________";
    cout << "\nFirst Name  : " << FirstName;
    cout << "\nLast Name   : " << LastName;
    cout << "\nFull Name   : " << FullName();
    cout << "\nEmail       : " << Email;
    cout << "\nPhone       : " << Phone;
    cout << "\nAcc. Number : " << _AccountNumber;
    cout << "\nPassword    : " << _PinCode;
    cout << "\nBalance     : " << _AccountBalance;
    cout << "\n__________________";
  }

  static clsBankClient Find(string AccountNumber) {
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;
      while (getline(MyFile, Line)) {

        clsBankClient Client = _ConvertLinetoClientObject(Line);

        if (Client.AccountNumber() == AccountNumber) {
          MyFile.close();
          return Client;
        }
      }

      MyFile.close();
    }
    return _GetEmptyClientObject();
  }

  static clsBankClient Find(string AccountNumber, string PinCode) {
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;
      while (getline(MyFile, Line)) {

        clsBankClient Client = _ConvertLinetoClientObject(Line);

        if (Client.AccountNumber() == AccountNumber &&
            Client.PinCode == PinCode) {
          MyFile.close();
          return Client;
        }
      }

      MyFile.close();
    }
    return _GetEmptyClientObject();
  }

  static bool IsClientExist(string AccountNumber) {
    clsBankClient Client = clsBankClient::Find(AccountNumber);
    return (!Client.IsEmpty());
  }

  enum enSaveResults {
    svFaildEmptyOBject = 0,
    svSucceeded = 1,
    svFaildAccountNumberExists = 2
  };

  enSaveResults Save() {
    switch (_Mode) {
    case enMode::enEmptyMode: {
      return enSaveResults::svFaildEmptyOBject;
    }
    case enMode::enUpdateMode: {
      _Update();
      return enSaveResults::svSucceeded;
      break;
    }
    case enMode::enAddNewMode: {
      if (clsBankClient::IsClientExist(_AccountNumber)) {
        return enSaveResults::svFaildAccountNumberExists;
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
    vector<clsBankClient> _vClients;
    _vClients = _LoadCleintsDataFromFile();

    for (clsBankClient &C : _vClients) {
      if (C.AccountNumber() == _AccountNumber) {
        C._MarkForDelete = true;
        break;
      }
    }

    _SaveCleintsDataToFile(_vClients);
    *this = _GetEmptyClientObject();

    return true;
  }

  void Deposit(double amount) {
    AccountBalance += amount;
    Save();
  }

  bool Withdraw(double amount) {
    if (amount > AccountBalance) {
      return false;
    } else {
      _AccountBalance -= amount;
      Save();
      return true;
    }
  }

  bool Transfer(double amount, clsBankClient &toClient, string username) {
    if (amount > AccountBalance) {
      return false;
    } else {
      Withdraw(amount);
      toClient.Deposit(amount);

      _RegisterTransferLog(toClient, amount, username);
      return true;
    }
  }

  static double GetTotalBalances() {
    vector<clsBankClient> vClients = clsBankClient::GetClientsList();
    double TotalBalances = 0;

    for (clsBankClient Client : vClients) {
      TotalBalances += Client.AccountBalance;
    }

    return TotalBalances;
  }

  static clsBankClient GetAddNewClientObject(string AccountNumber) {
    return clsBankClient(enMode::enAddNewMode, "", "", "", "", AccountNumber,
                         "", 0);
  }

  static vector<clsBankClient> GetClientsList() {
    return _LoadCleintsDataFromFile();
  }

  static vector<stTransferLogRec> GetTransferfLog() {
    vector<stTransferLogRec> vTransferLogRecord;
    fstream MyFile;

    MyFile.open(TransferLogFile, ios::in); // read Mode

    if (MyFile.is_open()) {
      string Line;
      stTransferLogRec TransLogRecord;

      while (getline(MyFile, Line)) {
        TransLogRecord = _ConvertTransferLogLineToRecord(Line);
        vTransferLogRecord.push_back(TransLogRecord);
      }

      MyFile.close();
    }

    return vTransferLogRecord;
  }
};
