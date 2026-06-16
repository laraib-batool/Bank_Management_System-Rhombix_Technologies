#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

/*
    Features:
    - Admin login
    - Create account
    - Deposit / Withdraw
    - Check balance
    - Close account
    - Transaction history
    - File handling (permanent storage)
*/

//ACCOUNT CLASS 
class Account {
public:
    int accNo;
    string name;
    double balance;
    vector<string> history;

    Account() {
        accNo = 0;
        name = "";
        balance = 0.0;
    }

    void showAccount() {
        cout << "\nAccount No: " << accNo;
        cout << "\nName      : " << name;
        cout << "\nBalance   : " << balance << endl;
    }

    void addHistory(string msg) {
        history.push_back(msg);
    }

    void showHistory() {
        cout << "\n--- Transaction History ---\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        for (string h : history) {
            cout << h << endl;
        }
    }
};

//BANK SYSTEM 
class BankSystem {
private:
    vector<Account> accounts;
    string filename = "bankdata.txt";

public:
    BankSystem() {
        loadFromFile();
    }

    //LOAD DATA
    void loadFromFile() {
        ifstream file(filename);
        if (!file) return;

        Account acc;
        while (file >> acc.accNo >> acc.name >> acc.balance) {
            accounts.push_back(acc);
        }
        file.close();
    }

    //SAVE DATA 
    void saveToFile() {
        ofstream file(filename);
        for (auto &acc : accounts) {
            file << acc.accNo << " "
                 << acc.name << " "
                 << acc.balance << endl;
        }
        file.close();
    }

    //FIND ACCOUNT
    int findAccount(int accNo) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].accNo == accNo)
                return i;
        }
        return -1;
    }

    //CREATE ACCOUNT 
    void createAccount() {
        Account acc;

        cout << "\nEnter Account Number: ";
        cin >> acc.accNo;

        if (findAccount(acc.accNo) != -1) {
            cout << "Account already exists!\n";
            return;
        }

        cout << "Enter Name: ";
        cin >> acc.name;

        cout << "Enter Initial Deposit: ";
        cin >> acc.balance;

        acc.addHistory("Account created with balance " + to_string(acc.balance));

        accounts.push_back(acc);
        saveToFile();

        cout << "Account created successfully!\n";
    }

    //DEPOSIT
    void deposit() {
        int accNo;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter Amount to Deposit: ";
        cin >> amount;

        accounts[index].balance += amount;
        accounts[index].addHistory("Deposited " + to_string(amount));

        saveToFile();

        cout << "Amount deposited successfully!\n";
    }

    //WITHDRAW
    void withdraw() {
        int accNo;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter Amount to Withdraw: ";
        cin >> amount;

        if (accounts[index].balance < amount) {
            cout << "Insufficient balance!\n";
            return;
        }

        accounts[index].balance -= amount;
        accounts[index].addHistory("Withdrawn " + to_string(amount));

        saveToFile();

        cout << "Amount withdrawn successfully!\n";
    }

    //CHECK BALANCE
    void checkBalance() {
        int accNo;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1) {
            cout << "Account not found!\n";
            return;
        }

        accounts[index].showAccount();
    }

    //CLOSE ACCOUNT 
    void closeAccount() {
        int accNo;

        cout << "\nEnter Account Number to Close: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1) {
            cout << "Account not found!\n";
            return;
        }

        accounts.erase(accounts.begin() + index);
        saveToFile();

        cout << "Account closed successfully!\n";
    }

    //TRANSACTION HISTORY 
    void showHistory() {
        int accNo;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1) {
            cout << "Account not found!\n";
            return;
        }

        accounts[index].showHistory();
    }
};

//ADMIN LOGIN 
bool adminLogin() {
    string user, pass;

    cout << "\n--- ADMIN LOGIN ---\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "1234") {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid credentials!\n";
        return false;
    }
}

//MAIN MENU 
int main() {
    BankSystem bank;

    if (!adminLogin()) {
        return 0;
    }

    int choice;

    do {
        cout << "\n BANK MENU \n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Close Account\n";
        cout << "6. Transaction History\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.checkBalance(); break;
            case 5: bank.closeAccount(); break;
            case 6: bank.showHistory(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
