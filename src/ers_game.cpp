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
    Cnsl::print("Thanks for playing!\n");
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
    // determine if its a match
    // handle if it is
    // handle if it isnt
    return false;
}

void EgyptianRatscrewGame::cardDown() {
    Player *currentPlayer = players[currentPlayerIdx];
    Cnsl::print(currentPlayer->name + "\n");
    // dequeue card from current player
    Card *nextCardDown = currentPlayer->getCard();
    // since there's only room on the keyboard for 2 players,
    // game should be over if nextCardDown is null (ie this player ran out of cards)
    if (!nextCardDown) { return; } 
    // if face card, start countdown
    int newCountdown = faceCardCountdownForRank(nextCardDown->rank);
    if (newCountdown > 0) { // if we have a new face card, start a new countdown
        faceCardCountdown = newCountdown;
        setToNextPlayer();
    } else if (faceCardCountdown > 0) { 
        // if countdown is positive, then we're in the middle of a countdown
        // TODO: handle case where countdown is slappable and countdown ran out
        faceCardCountdown--;
    } else {
        setToNextPlayer();
    }
    // TODO: if countdown runs out, center pile goes to other player
    Cnsl::print("countdown: " + std::to_string(faceCardCountdown)+ "\n");
    Cnsl::print("card: " + nextCardDown->toString() + "\n\n");
}

int EgyptianRatscrewGame::faceCardCountdownForRank(Card::Rank rank) {
    // If face card put down, next player has `n` chances to put down another face card
    // For Jack: `n` = 1, Queen:    `n` = 2, King:     `n` = 3, Ace:      `n` = 4
    switch (rank) {
    case Card::Rank::Ace:
        return 4;
    case Card::Rank::King:
        return 3;
    case Card::Rank::Queen:
        return 2;
    case Card::Rank::Jack:
        return 1;
    default:
        return 0; // no countdown for non-face cards
    }
}

void EgyptianRatscrewGame::setToNextPlayer() {
    currentPlayerIdx++;
    if (currentPlayerIdx >= players.size()) {
        currentPlayerIdx = 0;
    }
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