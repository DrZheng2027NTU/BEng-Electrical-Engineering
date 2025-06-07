#pragma once
#include"Headfile.h"
class GameBoard
{
private:
    int squares[38];  // Static array to store the price of each square

public:
    GameBoard();  // Constructor declaration
    int getSquarePrice(int index);  // Method declaration
    void printBoard();  // Method declaration
};
// Constructor definition
GameBoard::GameBoard() 
{
    srand(time(NULL));  // Initialize random seed
    squares[0] = 0;     // GO square
    for (int i = 1; i < 38; i++) 
    {
        if (i == 19) 
        {
            squares[i] = 0;  // JAIL square at position 20 (index 19)
        }
        else
        {
            squares[i] = rand() % 291 + 10;  // Random price between 10 and 300
        }
    }
}
// getSquarePrice method definition
int GameBoard::getSquarePrice(int index) 
{
    if (index >= 0 && index < 38) 
    {
        return squares[index];
    }
    else 
    {
        cout << "Index out of bounds!" << endl;
        return -1;  // Error case
    }
}
// printBoard method definition
void GameBoard::printBoard()
{
    cout << "Game Board Prices:" << endl;
    for (int i = 0; i < 38; i++) 
    {
        cout << "Square " << i << ": " << squares[i] << endl;
    }
}
