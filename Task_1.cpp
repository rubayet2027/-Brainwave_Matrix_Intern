#include <bits/stdc++.h>

using namespace std;

class Account {
private:
    string accountHolder;
    string pin;
    double balance;

public:
    Account(string holder, string pin, double initialBalance) {
        accountHolder = holder;
        this->pin = pin;
        balance = initialBalance;
    }

    bool validatePIN(string inputPIN) {
        return pin == inputPIN;
    }

    double checkBalance() {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful! New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful! New balance: " << balance << endl;
        } else {
            if (amount < 0){
                cout << "Invalid withdrawal amount "<< endl;
            }else if(amount > balance){
                cout<<"insufficient balance." <<endl;
            }
        }
    }

    void changePIN(string newPIN) {
        pin = newPIN;
        cout << "PIN successfully changed!" << endl;
    }
};

class ATM {
private:
    map<string, Account> accounts;  // To store account holder's name and account details

public:
    void addAccount(string accountHolder, string pin, double initialBalance) {
        accounts[accountHolder] = Account(accountHolder, pin, initialBalance);
    }

    void accessATM(string accountHolder, string pin) {
        if (accounts.find(accountHolder) != accounts.end()) {
            Account &account = accounts[accountHolder];
            if (account.validatePIN(pin)) {
                int choice;
                do {
                    cout << "\n--- ATM Menu ---" << endl;
                    cout << "1. Check Balance" << endl;
                    cout << "2. Deposit" << endl;
                    cout << "3. Withdraw" << endl;
                    cout << "4. Change PIN" << endl;
                    cout << "5. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1: {
                            cout << "Your balance is: " << account.checkBalance() << endl;
                            break;
                        }
                        case 2: {
                            double depositAmount;
                            cout << "Enter deposit amount: ";
                            cin >> depositAmount;
                            account.deposit(depositAmount);
                            break;
                        }
                        case 3: {
                            double withdrawAmount;
                            cout << "Enter withdrawal amount: ";
                            cin >> withdrawAmount;
                            account.withdraw(withdrawAmount);
                            break;
                        }
                        case 4: {
                            string newPIN;
                            cout << "Enter new PIN: ";
                            cin >> newPIN;
                            account.changePIN(newPIN);
                            break;
                        }
                        case 5: {
                            cout << "Thank you for using the ATM. Goodbye!" << endl;
                            break;
                        }
                        default: {
                            cout << "Invalid option. Please try again." << endl;
                            break;
                        }
                    }
                } while (choice != 5);
            } else {
                cout << "Invalid PIN!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

int main() {

    ATM atm;
    //we can add as many account as we want
    atm.addAccount("John Doe", "1234", 1000.0);
    atm.addAccount("Jane Smith", "4321", 1500.0);

    string accountHolder, pin;

    cout << "Welcome to the ATM!" << endl;
    cout << "Enter account holder name: ";
    cin >> accountHolder;

    cout << "Enter PIN: ";
    cin >> pin;

    atm.accessATM(accountHolder, pin);

    return 0;
}
