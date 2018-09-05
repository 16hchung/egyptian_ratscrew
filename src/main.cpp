#include "ers_game.h"
#include "main.h"

using cnsl = ConsoleHandler;

int main(int argc, char const *argv[])
{
    // char c = getch();
    cnsl::initWindow();
    playGame();
    cnsl::closeWindow();
    return 0;
}


void playGame() {
    EgyptianRatscrewGame game;
    cnsl::MoveType move = cnsl::waitForMove();
    // while (!game.isGameDone() && move != cnsl::QuitGame) {

//    }
}