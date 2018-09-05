#include "ers_game.h"
#include "main.h"

int main(int argc, char const *argv[])
{
    // char c = getch();
    ConsoleHandler::initWindow();
    EgyptianRatscrewGame game;
    game.printPlayers();
    ConsoleHandler::closeWindow();
    return 0;
}


void playGame() {

}