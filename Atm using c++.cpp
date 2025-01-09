#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ATM {
private:
    int balance;
    ofstream logFile;

public:
    ATM() {
        ifstream inputFile("balance.txt");
        if (inputFile.is_open()) {
            inputFile >> balance;
            inputFile.close();
        } else {
            balance = 450000;  
        }

        logFile.open("atm_log.txt", ios::app); 
        logFile << "ATM session started.\n";
    }

    ~ATM() {
        logFile << "ATM session ended.\n\n";
        logFile.close();


        ofstream outputFile("balance.txt");
        if (outputFile.is_open()) {
            outputFile << balance;
            outputFile.close();
        }
    }

    int getBalance() {
        logFile << "Balance Inquiry - Balance: " << balance << "\n";
        return balance;
    }

    bool withdraw(int amount) {
        if (amount > balance) {
            logFile << "Failed Withdrawal - Amount: " << amount << ", Insufficient Balance\n";
            return false;
        }
        balance -= amount;
        logFile << "Withdrawal - Amount: " << amount << ", Balance: " << balance << "\n";
        return true;
    }

    void deposit(int amount) {
        balance += amount;
        logFile << "Deposit - Amount: " << amount << ", Balance: " << balance << "\n";
    }
};

int main() {
    ATM atm;
    int choice, amount;
    char option;

    cout << "----------- ------------Welcome to Shreeyantra Bank ATM -------------------------------------------------------" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "WELCOME TO THE DASHBOARD" << endl;

    do {
        cout << "1. BALANCE INQUIRY" << endl;
        cout << "2. CASH WITHDRAWAL" << endl;
        cout << "3. CASH DEPOSIT" << endl;
        cout << "4. EXIT" << endl;
        cout << "ENTER YOUR DESIRED CHOICE: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "CURRENT BALANCE: " << atm.getBalance() << endl;
                break;
            case 2:
                cout << "Available balance: " << atm.getBalance() << endl;
                cout << "ENTER AMOUNT TO WITHDRAW: ";
                cin >> amount;
                if (atm.withdraw(amount)) {
                    cout << "Withdrawal successful" << endl;
                    cout << "Please collect your cash and card" << endl;
                } else {
                    cout << "Insufficient Balance..." << endl;
                    cout << "Transaction failed. Please collect your card and try again later." << endl;
                }
                break;
            case 3:
                cout << "Enter the Amount to deposit: ";
                cin >> amount;
                atm.deposit(amount);
                cout << "Deposit successful..." << endl;
                break;
            case 4:
                cout << "THANKS FOR CHOOSING SHREEYANTRA BANK" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
        
        cout << "DO YOU WANT TO CONTINUE WITH ANOTHER TRANSACTION [YES/NO]: ";
        cin >> option;
        system("cls");

    } while (option == 'y' || option == 'Y');

    return 0;
}

