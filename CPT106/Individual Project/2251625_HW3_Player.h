#pragma once
#include"Headfile.h"
class Player
{
private:
    string name;
    char gender;  // 'M' for male, 'F' for female
    int balance;
    int position;
public:
    // Constructor declaration
    Player(const string& name, char gender, int initialBalance, int initialPosition = 0);
    // Getter declarations
    string getName();
    char getGender();
    int getBalance();
    int getPosition();
    // Setter declarations
    void setPosition(int newPosition);
    // Method declarations
    void updateBalance(int amount);
    void printDetails();
    void save(ostream& out);
    void load(istream& in);
};
Player::Player(const string& name, char gender, int initialBalance, int initialPosition)
    : name(name), gender(gender), balance(initialBalance), position(initialPosition) {}
string Player::getName() 
{
    return name;
}
char Player::getGender() 
{
    return gender;
}
int Player::getBalance()
{
    return balance;
}
int Player::getPosition() 
{
    return position;
}
// Setter definition
void Player::setPosition(int newPosition) 
{
    position = newPosition;
}
// Method definitions
void Player::updateBalance(int amount) 
{
    balance += amount;
}
void Player::printDetails()
{
    cout << "Player: " << name
        << "\nGender: " << (gender == 'M' ? "Male" : "Female")
        << "\nBalance: " << balance
        << "\nPosition: " << position << endl;
}
void Player::save(ostream& out)
{
    out << name << " " << gender << " " << balance << " " << position << endl;
}
void Player::load(istream& in) 
{
    in >> name >> gender >> balance >> position;
}
