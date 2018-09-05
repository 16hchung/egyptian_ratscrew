#include "ers_game.h"
#include "main.h"

using cnsl = ConsoleHandler;

int main(int argc, char const *argv[])
{
    cnsl::initWindow();
    playGame();
    cnsl::closeWindow();
    return 0;
}


void playGame() {
    EgyptianRatscrewGame game;
    cnsl::MoveType move = cnsl::waitForMove();
    while (!game.isGameDone() && move != cnsl::QuitGame) {
        bool f_shouldQuit = false;
        switch (move) {
        case cnsl::Player1Slap: case cnsl::Player2Slap:
            game.playerSlappedCenter((int) move);
        case cnsl::CardDown:
            game.cardDown();
        case cnsl::QuitGame:
            f_shouldQuit = true;
        default:
            break;
        }
        if (f_shouldQuit) { break; }
        move = cnsl::waitForMove();
   }
}