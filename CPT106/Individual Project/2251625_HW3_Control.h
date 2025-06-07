#pragma once
#pragma once
#include "Headfile.h"
#include "Player.h"
#include "GameBoard.h"
class GameController
{
private:
    Player& player;//Receive a reference which can update the data ontime with time going
    Player& computer;//Receive a reference which can update the data ontime with time going
    GameBoard& board;//Receive a reference which can update the data ontime with time going
    bool gameRunning;
public:
    GameController(Player& player, Player& computer, GameBoard& board);
    bool isGameRunning();// Game running
    void processTurn();// Control the direction of move
    void processMove(Player& currentPlayer, bool isClockwise);// Go based on the number shown on the die
    int rollDice();
    void printGameStatus();
    void printFinalResults();
    void saveGame(const string& filename);
    void loadGame(const string& filename);
};
GameController::GameController(Player& player, Player& computer, GameBoard& board)
    : player(player), computer(computer), board(board), gameRunning(true) {}
bool GameController::isGameRunning() 
{
    return gameRunning;
}
void GameController::processTurn()
{
    if (gameRunning) 
    {
        processMove(player, true);  // Player moves clockwise
        if (gameRunning) 
        {
            processMove(computer, false);  // Computer moves anticlockwise
        }
    }
}
void GameController::processMove(Player& currentPlayer, bool isClockwise)
{
    int diceOutcome = rollDice();// Roll the dice and store the outcome
    cout << currentPlayer.getName() << " rolls a " << diceOutcome << std::endl;
    int newPosition = currentPlayer.getPosition() + (isClockwise ? diceOutcome : -diceOutcome);// Calculate the new position
    // Handle wrap-around at the ends of the board: if position exceeds board limits, wrap around
    if (newPosition >= 38)
    {
        newPosition -= 38;
    }
    else if (newPosition < 0)
    {
        newPosition += 38;
    }
    currentPlayer.setPosition(newPosition);// Set the player's position to the new, adjusted position
    if (newPosition == 19) // Jail landing
    {
        cout << currentPlayer.getName() << " lands on JAIL and loses the game." << std::endl;
        gameRunning = false;
        return;
    }
    int squarePrice = board.getSquarePrice(newPosition);// Price for going 
    if (squarePrice > currentPlayer.getBalance()) 
    {
        cout << currentPlayer.getName() << " cannot afford the price and loses the game." << std::endl;
        gameRunning = false;
    }
    else 
    {
        currentPlayer.updateBalance(-squarePrice);
        cout << currentPlayer.getName() << " moves to position " << newPosition
            << " and pays " << squarePrice << ". Remaining balance: " << currentPlayer.getBalance() << std::endl;
    }
}
int GameController::rollDice()
{
    return rand() % 6 + 1;  // Dice roll between 1 and 6
}
void GameController::printGameStatus()// Feedback ontime game status
{
    cout << "Current Game Status:" << endl;
    cout << player.getName() << " - Position: " << player.getPosition()
        << ", Balance: $" << player.getBalance() << endl;
    cout << computer.getName() << " - Position: " << computer.getPosition()
        << ", Balance: $" << computer.getBalance() << endl;
}
void GameController::printFinalResults() 
{
    cout << "Final Game Results:" << std::endl;
    cout << player.getName() << " - Final Balance: $" << player.getBalance() << std::endl;
    cout << computer.getName() << " - Final Balance: $" << computer.getBalance() << std::endl;
    if (player.getBalance() > computer.getBalance())
    {
        cout << player.getName() << " wins!" << endl;
    }
    else if (computer.getBalance() > player.getBalance()) 
    {
        cout << computer.getName() << " wins!" << endl;
    }
    else 
    {
        cout << "It's a tie!" << endl;
    }
}
void GameController::saveGame(const string& filename) // I/O game saving
{
    ofstream file(filename);
    if (file) 
    {
        player.save(file);
        computer.save(file);
        cout << "Game saved successfully in " << filename << ".\n";
    }
    else 
    {
        cout << "Unable to open file for saving at " << filename << ".\n";
    }
}
void GameController::loadGame(const string& filename) // File I/O 
{
    ifstream file(filename);
    if (file) 
    {
        player.load(file);
        computer.load(file);
        cout << "Game loaded successfully from " << filename << ".\n";
    }
    else 
    {
        cout << "No game data found or unable to open file at " << filename << ".\n";
    }
}
