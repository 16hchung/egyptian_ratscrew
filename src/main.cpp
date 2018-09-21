#include "ers_game.h"
#include "main.h"
#include <ncurses.h>

using Cnsl = ConsoleHandler;

int main(int argc, char const *argv[])
{
    Cnsl::initWindow();
    playGame();
    Cnsl::closeWindow();
    return 0;
}


void playGame() {
    EgyptianRatscrewGame game;
    game.play();
}