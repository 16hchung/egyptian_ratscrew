#include "ers_game.h"
#include "main.h"

int main(int argc, char const *argv[])
{
    // char c = getch();
    ConsoleHandler::initWindow();
    EgyptianRatscrewGame game;
    
    ConsoleHandler::closeWindow();
    game.printPlayers();
    return 0;
}


void playGame() {

}