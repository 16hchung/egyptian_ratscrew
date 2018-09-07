#include "ers_game.h"
#include "main.h"
#include <ncurses.h>

using Cnsl = ConsoleHandler;

int main(int argc, char const *argv[])
{
    Cnsl::initWindow();
    // Cnsl::MoveType move = Cnsl::waitForMove();
    // char c = getch();
    playGame();
    Cnsl::closeWindow();
    return 0;
}


void playGame() {
    EgyptianRatscrewGame game;
    Cnsl::MoveType move = Cnsl::waitForMove();
    while (!game.isGameDone() && move != Cnsl::QuitGame) {
        bool f_shouldQuit = false;
        switch (move) {
        // case Cnsl::Player1Slap: case Cnsl::Player2Slap:
        //     game.playerSlappedCenter((int) move);
            break;
        case Cnsl::CardDown:
            game.cardDown();
            break;
        case Cnsl::QuitGame:
        default:
            f_shouldQuit = true;
            break;
        }
        if (f_shouldQuit) { break; }
        move = Cnsl::waitForMove();
   }
}