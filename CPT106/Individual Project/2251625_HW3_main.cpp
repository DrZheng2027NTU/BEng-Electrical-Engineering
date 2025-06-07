#include"Player.h"
#include"Gameboard.h"
#include"Control.h"
#include"Interaction.h"
#include"Headfile.h"
#include"UserLogin.h"
int main() 
{
    UserLogin userLogin;
    Player player1 = userLogin.displayLoginMenu();  // New or old account
    string pcName = "CPT106";
    Player computer(pcName, 'M', 1500, 0);  // Computer always resets
    GameBoard board;
    GameController gameController(player1, computer, board);
    if (userLogin.getIsNewAccount()) 
    {
        // If new users, start new game
    }
    else
    {
        gameController.loadGame("game_state1.txt");  // If old users, call the old game again
    }

    UIController uiController(gameController);
    uiController.startInterface();  // Start game interface

    gameController.saveGame("game_state1.txt");  // Save status after game

    cout << "Final player status:\n";
    player1.printDetails();
    computer.printDetails();
    return 0;
}
