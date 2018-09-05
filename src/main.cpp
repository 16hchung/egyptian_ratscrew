#include "console_handler.h"
#include "ers_game.h"
#include "main.h"

int main(int argc, char const *argv[])
{
    // initWindow();
    // char c = getch();
    // EgyptianRatscrewGame game;
    // closeWindow();
    Deck deck;
    Player player1("hi1");
    Player player2("hi2");
    std::vector<Player *> players = {&player1, &player2};
    deck.deal(players);
    player1.print();
    player2.print();
    return 0;
}


void playGame() {

}