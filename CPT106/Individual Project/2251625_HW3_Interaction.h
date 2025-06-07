#pragma once
#include"Headfile.h"
#include"Control.h"
class UIController
{
private:
    GameController gameController;

public:
    UIController(const GameController& controller);// Constructor declaration
    void startInterface();// StartInterface method definition
    void showWelcomeMessage();// ShowWelcomeMessage method definition
    void showGameState();// ShowGameState method definition
    void showGameOver();// ShowGameOver method definition
};
UIController::UIController(const GameController& controller) : gameController(controller) {}
void UIController::startInterface()
{
    showWelcomeMessage();
    string input;
    while (gameController.isGameRunning())
    {
        showGameState();
        cout << "Enter 'roll' to roll the dice, or 'quit' to exit: " << endl;
        getline(cin, input);
        if (input == "quit")
        {
            cout << "Exiting game." << endl;
            break;
        }
        else if (input == "roll")
        {
            gameController.processTurn();
        }
        else
        {
            cout << "Invalid command. Please try again." << endl;
        }
    }
    showGameOver();
}
void UIController::showWelcomeMessage()
{
    cout << "Welcome to Luck Draw!" << endl;
    cout << "You and the computer will start at the 'GO' square." << endl;
}
void UIController::showGameState()
{
    gameController.printGameStatus(); // Assumes printGameStatus is implemented in GameController
}
void UIController::showGameOver()
{
    cout << "Game Over. Here are the final results:" << endl;
    gameController.printFinalResults(); // Assumes printFinalResults is implemented in GameController
}

