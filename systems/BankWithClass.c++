#include <string.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class BankAccount
{
private:
    string accountNumber;
    string ownerName;
    double balance;

public:
    //  constructor
    BankAccount(const string &account, const string &ownerName, double amount) : accountNumber(account), ownerName(ownerName), balance(amount) {};
    BankAccount() : accountNumber(""), ownerName(""), balance(0.0) {};

    void deposit(double cash)
    {
        balance += cash;
        cout << "successfull deposited your cash" << endl;
        // cout << "Your New Balance : " << balance << endl;
    }
    bool withdraw(double cash)
    {
        if (cash > balance)
        {
            cout << "Mhhhm! Ain't enough Money to withdraw ~(*--*)~ !!" << endl;
            cout << "your current balance : " << balance <<endl;
            return false;
        }
        else
        {
            balance -= cash;
            cout << "Successfully witdrawed your Money" << endl;
            // cout << "Your New Balance : " << balance << endl;
            return true;
        }
    }
};
double checkBalance(string accountNumber)
{
    ifstream databaseFile("./files/database.csv");

    if (databaseFile.is_open())
    {
        string line;
        getline(databaseFile, line);
        
        while (getline(databaseFile,line))
        {
            stringstream ss(line);
            string name, account, balance;

            // Get each column using getline with comma delimiter
            getline(ss, name, ',');
            getline(ss, account, ',');
            getline(ss, balance, ',');

            if (account == accountNumber)
            {
                return stod(balance);
                databaseFile.close();
            }
           
        }
             cout << "Account Not found ! " << endl;
             databaseFile.close();
    };

    return 0;
}

void recordIntoCsv(string name, string account, double balance)
{
    // First check if file exists
    ifstream checkFile("./files/database.csv");
    bool fileExists = checkFile.good();
    checkFile.close();

    // Open file in append mode
    ofstream databaseFile("./files/database.csv", fileExists ? ios::app : ios::out);

    if (!databaseFile)
    {
        cout << "Error opening files!" << endl;
        return;
    }

    if (databaseFile.is_open())
    {
        // Write header only if file is new
        if (!fileExists)
        {
            databaseFile << "Owner_Name,Account_number,Balance\n";
        }
        // Append new user data
        databaseFile << name << "," << account << "," << balance << "\n";
        databaseFile.close();
        cout << "You are now a member of our KIMINA COMMUNITY !! " << endl;
    }
    else
    {
        cout << "Mmmma Bombo00clatttt sth went Wrong, wait and we retry ! ... " << endl;
    }
}

void UpdateBalanceInDatabaseCSV(string accountNumber, double amount, bool deposit)
{
    ifstream inFile("./files/database.csv");
    ofstream tempFile("./files/temp.csv");

    if (!inFile || !tempFile)
    {
        cout << "Error opening files!" << endl;
        return;
    }

    string line;
    // Copy header
    getline(inFile, line);
    tempFile << line << "\n";

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string name, account, balance;

        // Get each column using getline with comma delimiter
        getline(ss, name, ',');
        getline(ss, account, ',');
        getline(ss, balance, ',');

        if (account == accountNumber && deposit == true)
        {
            double newBalance = stod(balance) + amount;
            tempFile << name << "," << account << "," << newBalance <<"\n";
        }
        else if (account == accountNumber && deposit == false)
        {
            double newBalance = stod(balance) - amount;
            tempFile << name << "," << account << "," << newBalance <<"\n";
        }
        else
        {
            // Copy original line for other accounts
            tempFile << line << "\n";
        }
    }

    inFile.close();
    tempFile.close();

    // Replace original file with updated file
    remove("./files/database.csv");
    rename("./files/temp.csv", "./files/database.csv");
}

bool accountAlreadyExists(string accountToFind)
{
    ifstream databaseFile("./files/database.csv");

    if (databaseFile.is_open())
    {
        string line;

        // skipping the header
        getline(databaseFile, line);

        while (getline(databaseFile, line))
        {
            stringstream ss(line);
            string ownerName, account, balance;

            // Get each column using getline with comma delimiter
            getline(ss, ownerName, ',');
            getline(ss, account, ',');
            getline(ss, balance, ',');

            if (account == accountToFind)
            {
                cout << "acount found" << endl;
                databaseFile.close();
                return true;
            }
        }

        databaseFile.close();
        return false;
    }
    return false;
}

BankAccount gettingYourAccount(string accountNumber)
{
    ifstream databaseFile("./files/data.csv");

    if (databaseFile.is_open())
    {
        string line;
        string acccountNumber;
        // skipping the header
        getline(databaseFile, line);

        while (getline(databaseFile, line))
        {

            stringstream ss(line);
            string ownerName, account, balance;

            // Get each column using getline with comma delimiter
            getline(ss, ownerName, ',');
            getline(ss, account, ',');
            getline(ss, balance, ',');

            if (account == accountNumber)
            {
                // stod  ===> transforming the results into a double
                account.erase(remove(account.begin(), account.end(), ' '), account.end());
                transform(account.begin(), account.end(), account.begin(), ::toupper);

                BankAccount client(account, ownerName, stod(balance));
                return client;
                cout << " successffully got you In ." << endl;
            }
            else
            {
                cout << " Account Not Fount !" << endl;
                return BankAccount();
            }
        }
    }
}

int main()
{
    string ownerName;
    string accountNumber;
    double balance;
    int option1;
    int option;
    BankAccount client;

    cout << "Welcome to IKIMINA BANK ACCOUNT " << endl;
    cout << "=================================" << endl;
    cout << "CREATE an Account if its for the first time or proceed : " << endl
         << "1. create an account " << endl
         << "2. Already have an account -> proceed " << endl
         << "3. to exit " << endl
         << "Your Choice : ";
    cin >> option1;

    if (option1 == 1)
    {
        // checking if the user tricked us and they already had the account
        cout << "Alright stay vigilent , while in the process of create your accout " << endl
             << "Provide:" << endl
             << "Your name :";
        cin >> ownerName;
        cout << "Account Number (e.x: KM[****]): ";
        cin >> accountNumber;

        // removing space in the string and transforming to upper case
        accountNumber.erase(remove(accountNumber.begin(), accountNumber.end(), ' '), accountNumber.end());
        transform(accountNumber.begin(), accountNumber.end(), accountNumber.begin(), ::toupper);

        cout << "balance : ";
        cin >> balance;

        if (accountAlreadyExists(accountNumber))
        {
            cout << "Your account already exists # And We have automatically Loged you in " << endl;
            cout << "Please do not forget again you BOMBOCLAAT account Number (*/o-0-o/*) " << endl;
            client = gettingYourAccount(accountNumber);
        }
        else
        {
            // removing space in the string and transforming to upper case
            accountNumber.erase(remove(accountNumber.begin(), accountNumber.end(), ' '), accountNumber.end());
            transform(accountNumber.begin(), accountNumber.end(), accountNumber.begin(), ::toupper);

            client = BankAccount(accountNumber, ownerName, balance);
            recordIntoCsv(ownerName, accountNumber, balance);
            cout << "Successfully created your Account" << endl;
        }
    }
    else if (option1 == 2)
    {
        // setting account to nothing
        accountNumber = "";
        cout << "Provide your account Number " << endl;
        cout << "your Account Number (e.x: KM[****]):";
        cin >> accountNumber;

        // removing space in the string and transforming to upper case
        accountNumber.erase(remove(accountNumber.begin(), accountNumber.end(), ' '), accountNumber.end());
        transform(accountNumber.begin(), accountNumber.end(), accountNumber.begin(), ::toupper);

        // cout<<accountNumber<<endl;
        if (accountAlreadyExists(accountNumber))
        {
            client = gettingYourAccount(accountNumber);
        }
        else
        {
            cout << "Bad man your account do not Bomboclat exists Bye (o^_^o) !" << endl;
            return 0;
        }
    }
    else if (option1 == 3)
    {
        return 0;
    }

    cout << "You can now DEPOSIT or WITHDRAW from your account" << endl;
    cout << " Choose : " << endl
         << "1. DEPOSIT " << endl
         << "2. WITHDRAW " << endl
         << "3. Check Balance " << endl
         << "4. to exit" << endl;

    // transaction logic

    while (true)
    {
        cout << "Your option : ";
        cin >> option;
        if (option == 1)
        {
            double cash;
            cout << "Enter the amount you want to deposit (^--^) : ";
            cin >> cash;
            client.deposit(cash);
            UpdateBalanceInDatabaseCSV(accountNumber, cash, true);
            cout<< " your New  balance :"<<checkBalance(accountNumber)<<endl;

        }
        else if (option == 2)
        {
            int dedacted;
            cout << "Enter the amount you want to withdraw (^--^) : ";
            cin >> dedacted;
            client.withdraw(dedacted);
            UpdateBalanceInDatabaseCSV(accountNumber, dedacted, false);
            cout<< " your New  balance :"<<checkBalance(accountNumber)<<endl;
            
        }
        else if (option == 3)
        {
            cout << checkBalance(accountNumber) <<endl;
        }
        else if (option == 4)
        {
            cout << "Thank you for being our vigilent customer to day !" << endl;
            cout << "we wish you to return back ";
            break;
        }
        else
        {
            cout << "Service not found (-_-) try again" << endl;
            return 0;
        }
    }

    return 0;
}