#include <string.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

int find_largest(int nums[], int n)
{                                        // Function definition for finding the largest element in an array
    return *max_element(nums, nums + n); // Return the maximum element in the array using max_element from algorithm library
};

const double PI = 3.14159;

class Circle
{
private:
    float radius;

public:
    Circle(double r) : radius(r) {};
    float area()
    {
        float area;
        return area = PI * pow(radius, 2);
    }
};

class BankAccount
{
private:
    string accountNumber;
    double balance;

public:
    BankAccount(string &account, double amount) : accountNumber(account), balance(amount) {};
    void deposit(double cash)
    {
        balance += cash;
        cout << "successfull deposited your cash" << endl;
        cout << "Your New Balance : " << balance << endl;
    }
    void withdraw(double cash)
    {
        if (cash > balance)
        {
            cout << "oops! Ain't no Money ~(*--*)~ , You're Broke !!" << endl;
            cout << "your balance : " << balance;
        }
        balance -= cash;
        cout << "Successfully witdrawed your Money" << endl;
        cout << "Your New Balance : " << balance << endl;
    }
};

int main()
{
    string account;
    double balance;
    int option;
    cout << "Welcom to IKIMINA BANK ACCOUNT " << endl;
    cout << "=================================" << endl;
    cout << "Provide:" << endl
         << "account name :";
    cin >> account;
    cout << "balance : ";
    cin >> balance;
    BankAccount client(account, balance);
    cout << "Successfully created your Account" << endl
         << "You can now DEPOSIT or WITHDRAW from your account" << endl;
    cout << " Choose : " << endl
         << "1. DEPOSIT " << endl
         << "2. WITHDRAW " << endl
         << "3. to exit " << endl;
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
        }
        else if (option == 2)
        {
            int dedacted;
            cout << "Enter the amount you want to withdraw (^--^) : ";
            cin >> dedacted;
            client.withdraw(dedacted);
        }else if(option == 3){
            cout<<"Thank you for being our vigilent customer to day !"<<endl;
            cout<<"we wish you to return back ";
            break;
        }else
        {
            cout << "Service not found (-_-) try again" << endl;
        }
    }

    return 0;
}