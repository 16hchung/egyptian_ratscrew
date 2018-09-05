#include "ers_game.h"
#include "console_handler.h"

using Cnsl = ConsoleHandler;

EgyptianRatscrewGame::EgyptianRatscrewGame() {
    printIntro();
    initPlayers();
    deck.deal(players);
}

EgyptianRatscrewGame::~EgyptianRatscrewGame() {
    for (Player *player : players) {
        delete player;
    }
    Cnsl::print("A quick note: credit for playing card ASCII art goes to ejm98\n");
    Cnsl::print("Link to art here: https://www.asciiart.eu/miscellaneous/playing-cards\n\n");
    Cnsl::print("Thanks for playing!");
}

void EgyptianRatscrewGame::printIntro() {
    Cnsl::print("Welcome to Egyptian Ratscrew!\n");
    Cnsl::print("Want a rundown of how to play?\n");
    // TODO: print instructions
}

void EgyptianRatscrewGame::initPlayers() {
    std::string player1Name = Cnsl::getInput("What is player 1's name? ");
    std::string player2Name = Cnsl::getInput("What is player 2's name? ");

    Player *player1 = new Player(player1Name);
    Player *player2 = new Player(player2Name);
    players.push_back(player1);
    players.push_back(player2);
}

bool EgyptianRatscrewGame::playerSlappedCenter(int playerIdx) {
    return false;
}

void EgyptianRatscrewGame::cardDown() {
    
}

bool EgyptianRatscrewGame::isGameDone() {
    for (Player *player : players) {
        if (player->getScore() >= Card::stdDeckCount) {
            return true;
        }
    }
    return false;
}

void EgyptianRatscrewGame::printPlayers() {
    for (Player *player : players) {
        player->print();
    }
}