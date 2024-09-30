#include <bits/stdc++.h>

using namespace std;

class BankAccount {
private:
    string accountHolder;
    string accountNumber;
    double balance;
    int pin;  

public:
    BankAccount() {
        accountHolder = "No Name";
        accountNumber = "ACC00000";
        balance = 0.00;
        pin = 0000; 
    }

    BankAccount(string holder, string accNum, double initialBalance, int initialPin) {
        accountHolder = holder;
        accountNumber = accNum;
        balance = initialBalance;
        pin = initialPin;
    }

    string getAccountNumber() {
        return accountNumber;
    }

    string getAccountHolder() {
        return accountHolder;
    }

    double getBalance() {
        return balance;
    }

    bool verifyPin(int enteredPin) {
        return pin == enteredPin;
    }

    
    void setPin(int newPin) {
        pin = newPin;
        cout << "PIN changed successfully!" << endl;
    }

    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful.\nNew balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful.\nNew balance: $" << fixed << setprecision(2) << balance << endl;
            return true;
        } else {
            cout << "Invalid amount or insufficient funds." << endl;
            return false;
        }
    }

    bool transfer(double amount, BankAccount &toAccount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            return true;
        }
        return false;
    }
};

// Function to generate a unique account number
string generateAccountNumber(int accountId) {
    return "ACC" + to_string(1000 + accountId);
}

// Function to find account by account number
int findAccountByNumber(vector<BankAccount> &accounts, string accountNumber) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accountNumber) {
            return i;
        }
    }
    return -1;
}

bool verifyPinForAccount(BankAccount &account) {
    int enteredPin;
    cout << "Enter your 4-digit PIN: ";
    cin >> enteredPin;

    if (account.verifyPin(enteredPin)) {
        cout << "PIN verified successfully." << endl;
        return true;
    } else {
        cout << "Incorrect PIN. Transaction aborted." << endl;
        return false;
    }
}

int main() {
    vector<BankAccount> accounts;
    int option;

    cout << "Welcome to the Online Banking System!" << endl;

    do {
        cout << "\n\t--- Main Menu ---" << endl;
        cout << "\n\t1. Create Account" << endl;
        cout << "\t2. Deposit Funds" << endl;
        cout << "\t3. Withdraw Funds" << endl;
        cout << "\t4. Transfer Funds" << endl;
        cout << "\t5. Check Balance" << endl;
        cout << "\t6. Change PIN" << endl;
        cout << "\t7. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {  //Create Account
                string name;
                double initialDeposit;
                int pin;
                
                cout << "Fill up your information please.\n";
                cout << "Enter account holder name: ";
                cin.ignore();  // Clear buffer
                getline(cin, name);
                cout << "Set a 4-digit PIN for your account: ";
                cin >> pin;
                cout << "Enter initial deposit amount: ";
                cin >> initialDeposit;

                if (initialDeposit < 0) {
                    cout << "Initial deposit must be non-negative." << endl;
                } else {
                    string accountNumber = generateAccountNumber(accounts.size());
                    accounts.push_back(BankAccount(name, accountNumber, initialDeposit, pin));
                    cout << "Account created successfully! Your account number is: " << accountNumber << endl;
                }
                break;
            }

            case 2: { // Deposit Funds
                string accountNumber;
                double depositAmount;

                cout << "Enter account number: ";
                cin >> accountNumber;

                int accountIndex = findAccountByNumber(accounts, accountNumber);
                if (accountIndex != -1) {
                    if (verifyPinForAccount(accounts[accountIndex])) {
                        cout << "Enter deposit amount: ";
                        cin >> depositAmount;
                        accounts[accountIndex].deposit(depositAmount);
                    }
                } else {
                    cout << "Account not found.\nCreate Your Account." << endl;
                }
                break;
            }

            case 3: {  // Withdraw Funds
                string accountNumber;
                double withdrawAmount;

                cout << "Enter account number: ";
                cin >> accountNumber;

                int accountIndex = findAccountByNumber(accounts, accountNumber);
                if (accountIndex != -1) {
                    if (verifyPinForAccount(accounts[accountIndex])) {
                        cout << "Enter withdrawal amount: ";
                        cin >> withdrawAmount;
                        accounts[accountIndex].withdraw(withdrawAmount);
                    }
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }

            case 4: {  // Transfer Funds
                string fromAccountNumber, toAccountNumber;
                double transferAmount;

                cout << "Enter your account number: ";
                cin >> fromAccountNumber;
                cout << "Enter recipient's account number: ";
                cin >> toAccountNumber;
                cout << "Enter transfer amount: ";
                cin >> transferAmount;

                int fromAccountIndex = findAccountByNumber(accounts, fromAccountNumber);
                int toAccountIndex = findAccountByNumber(accounts, toAccountNumber);

                if (fromAccountIndex != -1 && toAccountIndex != -1) {
                    if (verifyPinForAccount(accounts[fromAccountIndex])) {
                        if (accounts[fromAccountIndex].transfer(transferAmount, accounts[toAccountIndex])) {
                            cout << "Transfer successful." << endl;
                        }
                    }
                } else {
                    cout << "One or both account numbers were not found.\nPlease create account." << endl;
                }
                break;
            }

            case 5: {  // Check Balance
                string accountNumber;

                cout << "Enter account number: ";
                cin >> accountNumber;

                int accountIndex = findAccountByNumber(accounts, accountNumber);
                if (accountIndex != -1) {
                    if (verifyPinForAccount(accounts[accountIndex])) {
                        cout << "Account Holder: " << accounts[accountIndex].getAccountHolder() << endl;
                        cout << "Current Balance: $" << fixed << setprecision(2) << accounts[accountIndex].getBalance() << endl;
                    }
                } else {
                    cout << "Account not found.\nCreate Your Account." << endl;
                }
                break;
            }

            case 6: {  // Change PIN
                string accountNumber;
                int newPin;

                cout << "Enter your account number: ";
                cin >> accountNumber;

                int accountIndex = findAccountByNumber(accounts, accountNumber);
                if (accountIndex != -1) {
                    if (verifyPinForAccount(accounts[accountIndex])) {
                        cout << "Enter your new 4-digit PIN: ";
                        cin >> newPin;
                        accounts[accountIndex].setPin(newPin);
                    }
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }

            case 7: {  // Exit
                cout << "Thank you for using the Online Banking System. Goodbye!" << endl;
                break;
            }

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }

    } while (option != 7);

    return 0;
}
