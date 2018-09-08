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
    std::string player1Name = Cnsl::getInput(Player::maxNameLen, "What is player 1's name? ");
    std::string player2Name = Cnsl::getInput(Player::maxNameLen, "What is player 2's name? ");

    // keyboard is only large enough to accomodate two players
    Player *player1 = new Player(player1Name);
    Player *player2 = new Player(player2Name);
    players.push_back(player1);
    players.push_back(player2);
}

bool EgyptianRatscrewGame::playerSlappedCenter(int playerIdx) {
    bool wrongSlap = false;
    if (!wrongSlap) {
    } 
    // determine if its a match
    // handle if it is
    // handle if it isnt
    return false;
}

void EgyptianRatscrewGame::cardDown() {
    Player *currentPlayer = players[currentPlayerIdx];
    assert(currentPlayer);
    // dequeue card from current player
    Card *nextCardDown = currentPlayer->getCard();
    // since there's only room on the keyboard for 2 players,
    // game should be over if nextCardDown is null (ie this player ran out of cards)
    if (!nextCardDown) { 
        Cnsl::print("no card down\n"); // TODO: delete this
        return;
    } 
    bool startedNewCountdown, wasInCountdown, countDownFinished;
    centerPile.addCard(nextCardDown, startedNewCountdown, wasInCountdown, countDownFinished);
    Cnsl::print("card: " + nextCardDown->toString() + "\n");
    Cnsl::print(players[0]->name + ": " + std::to_string(players[0]->getScore()) + "\n");
    Cnsl::print(players[1]->name + ": " + std::to_string(players[1]->getScore()) + "\n\n");

    // player only gets switched if no former countdown *that persisted*
    // (still switch if new countdown interrupts)
    if (startedNewCountdown || !wasInCountdown) {
        nextPlayerTurn();
        return;
    }
    // if we are in the middle of a countdown and there is no new face card to reset it
    if (!countDownFinished) { return; }
    // if countdown is over and pile is not slappable, then last player gets center pile,
    // otherwise leave it alone
    CenterCardPile::SlapType slap = centerPile.currentSlapType();
    if (slap == CenterCardPile::Invalid) {
        Player *lastPlayer = getLastPlayer();
        assert(lastPlayer);
        centerPile.giveCardsToPlayer(lastPlayer);
        nextPlayerTurn();
    }
}

void EgyptianRatscrewGame::nextPlayerTurn() {
    currentPlayerIdx++;
    if (currentPlayerIdx >= players.size()) {
        currentPlayerIdx = 0;
    }
}

Player *EgyptianRatscrewGame::getLastPlayer() {
    int playerIdx = (currentPlayerIdx <= 0) ? players.size() - 1 : currentPlayerIdx - 1;
    return players[playerIdx];
}

bool EgyptianRatscrewGame::isGameDone() {
    for (Player *player : players) {
        assert(player);
        if (player->getScore() <= 0) {
            return true;
        }
    }
    return false;
}

void EgyptianRatscrewGame::printPlayers() {
    for (Player *player : players) {
        assert(player);
        player->print();
    }
}