#pragma once
#pragma once
#include"Headfile.h"
#include "Player.h"  //Include the player 
class UserLogin 
{
private:
    bool isNewAccount;
public:
    UserLogin();  // Constructor declaration
    bool getIsNewAccount();  // Getter declaration
    Player displayLoginMenu();  // Menu function declaration
    Player createAccount();  // Account creation declaration
    Player login();  // Login function declaration
};
UserLogin::UserLogin() : isNewAccount(false) {}
bool UserLogin::getIsNewAccount()
{
    return isNewAccount;
}
Player UserLogin::displayLoginMenu() 
{
    int choice;
    cout << "1. Create New Account\n";
    cout << "2. Login to Existing Account\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) // Try switch case
    {
    case 1:
        isNewAccount = true;
        return createAccount();
    case 2:
        isNewAccount = false;
        return login();
    case 3:
        exit(0);
    default:
        cout << "Invalid choice, please try again.\n";
        return displayLoginMenu();
    }
}
Player UserLogin::createAccount() 
{
    string name, password;
    char gender;
    int balance = 5000;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter gender (M/F): ";
    cin >> gender;
    ofstream outFile("accounts.txt", ios::app);
    outFile << name << " " << password << " " << gender << " " << balance << "\n";
    outFile.close();
    cout << "Account created successfully.\n";
    return Player(name, gender, balance);
}
Player UserLogin::login() 
{
    string inputName, inputPassword;
    char gender;
    int balance;
    cout << "Enter your name: ";
    cin >> inputName;
    cout << "Enter password: ";
    cin >> inputPassword;
    ifstream inFile("accounts.txt");
    string name, password;
    while (inFile >> name >> password >> gender >> balance)
    {
        if (name == inputName && password == inputPassword) 
        {
            cout << "Login successful!\n";
            return Player(name, gender, balance);
        }
    }
    inFile.close();
    cout << "Invalid login details. Please try again.\n";
    return login();
}
