#include "ers_game.h"
#include "console_handler.h"

using Cnsl = ConsoleHandler;
using Rank = Card::Rank;

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
        Cnsl::print("no card down\n");
        return;
    } 
    addToCenterPile(nextCardDown);

    /* Handle face card case... */
    int newCountdown = faceCardCountdownForRank(nextCardDown->rank);

    // if we have a new face card, or if we're not currently in the middle of a countdown, reset
    if (newCountdown > 0 || faceCardCountdown <= 0) {
        faceCardCountdown = newCountdown;
        setToNextPlayer(); // player only gets switched if no former persistent countdown
        // return;
    } else {

    // if we are in the middle of a countdown and there is no new face card to reset it
    faceCardCountdown--;
    if (faceCardCountdown > 0) { 
        Cnsl::print("countdown not done\n");
        return; 
    }
    // if countdown is over and pile is not slappable, then last player gets center pile,
    // otherwise leave it alone
    SlapType slap = currentSlapType();
    if (slap == Invalid) {
        Player *lastPlayer = getLastPlayer();
        assert(lastPlayer);
        lastPlayer->addCards(centerPile);
        resetCenterPile();
        setToNextPlayer();
    }
    }
    Cnsl::print(players[0]->name + ": " + std::to_string(players[0]->getScore()) + "\n");
    Cnsl::print(players[1]->name + ": " + std::to_string(players[1]->getScore()) + "\n");
    Cnsl::print("countdown: " + std::to_string(faceCardCountdown)+ "\n");
    Cnsl::print("card: " + nextCardDown->toString() + "\n\n");

}

void EgyptianRatscrewGame::resetCenterPile() {
    faceCardCountdown = 0;
    bottom = secondToTop = thirdToTop = nullptr;
}

int EgyptianRatscrewGame::faceCardCountdownForRank(Card::Rank rank) {
    // If face card put down, next player has `n` chances to put down another face card
    // For Jack: `n` = 1, Queen:    `n` = 2, King:     `n` = 3, Ace:      `n` = 4
    switch (rank) {
    case Rank::Ace:
        return 4;
    case Rank::King:
        return 3;
    case Rank::Queen:
        return 2;
    case Rank::Jack:
        return 1;
    default:
        return 0; // no countdown for non-face cards
    }
}

void EgyptianRatscrewGame::addToCenterPile(Card *card) {
    Card *oldTop = (centerPile.empty()) ? nullptr : centerPile.top();
    centerPile.push(card);
    // update center pile pointers
    if (bottom == nullptr) {
        assert(centerPile.size() == 1);
        bottom = card;
    }
    thirdToTop = secondToTop;
    secondToTop = oldTop;
}

EgyptianRatscrewGame::SlapType EgyptianRatscrewGame::currentSlapType() {
    // can't have a slap with just one card
    if (centerPile.size() <= 1 || !secondToTop) { 
        return Invalid;
    }
    assert(secondToTop && bottom);
    Card *top = centerPile.top();
    Rank topRank = top->rank;
    Rank secondRank = secondToTop->rank; // no line for thirdRank because might be null
    Rank bottomRank = bottom->rank;
    SlapType slap = Invalid; // start out assuming there is no slap
    // Check for 2-card slaps...
    if (topRank == secondRank) {
        slap = Double;
    } else if (cardPairHasRanks(top, secondToTop, Rank::King, Rank::Queen)) {
        slap = Marriage;
    } else if (cardPairHasRanks(top, secondToTop, Rank::King, Rank::Jack)) {
        slap = Rainbow;
    } else if (cardPairHasRanks(top, secondToTop, Rank::Queen, Rank::Jack)) {
        slap = Affair;
    // Check for 3-card slaps...
    } else if (thirdToTop && topRank == thirdToTop->rank) {
        slap = Sandwich;
    } else if (topRank == bottomRank) {
        slap = TopBottom;
    }    
    return slap;
}

bool EgyptianRatscrewGame::cardPairHasRanks(Card *card1, Card *card2, Rank rank1, Rank rank2) {
    return (card1->rank == rank1 && card2->rank == rank2) 
        || (card1->rank == rank2 && card2->rank == rank1);
}

void EgyptianRatscrewGame::setToNextPlayer() {
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