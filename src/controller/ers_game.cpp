#include "ers_game.h"
#include "console_handler.h"
#include "main_center_pile_view.h"
#include "burn_center_pile_view.h"

using Cnsl = ConsoleHandler;

EgyptianRatscrewGame::EgyptianRatscrewGame() {
    printIntro();
    initPlayers();
    initViews();
    deck.deal(players);
}

EgyptianRatscrewGame::~EgyptianRatscrewGame() {
    for (Player *player : players) {
        delete player;
    }
    delete centerPileView;
    delete burnPileView;
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

void EgyptianRatscrewGame::initViews() {
    centerPileView = new MainCenterPileView();
    burnPileView = new BurnCenterPileView();
}

void EgyptianRatscrewGame::playerSlappedCenter(int playerIdx) {
    if (centerPile.numCards() <= 0) { return; } // if multiple slaps in a row, only process the first
    assert(0 <= playerIdx && playerIdx < players.size());
    Player *player = players[playerIdx];
    assert(player);
    // determine if pile is slappable
    CenterCardPile::SlapType slap = centerPile.currentSlapType();
    if (slap == CenterCardPile::Invalid) {
        Cnsl::print("Invalid slap: " + player->name + "\n");
        Card *card = player->getCard();
        centerPile.burnCard(card);
    } else {
        Cnsl::print("Valid slap: " + player->name + "\n");
        centerPile.giveCardsToPlayer(player);
        currentPlayerIdx = playerIdx;
    }
    return;
}

void EgyptianRatscrewGame::cardDown() {
    Player *currentPlayer = getCurrentPlayer();
    // dequeue card from current player
    Card *nextCardDown = currentPlayer->getCard();
    // since there's only room on the keyboard for 2 players,
    // game should be over if nextCardDown is null (ie this player ran out of cards)
    if (!nextCardDown) { 
        return;
    } 
    bool startedNewCountdown, wasInCountdown, countDownFinished;
    centerPile.addCard(nextCardDown, startedNewCountdown, wasInCountdown, countDownFinished);
    centerPileView->printCard(nextCardDown);
    // Cnsl::print(players[0]->name + ": " + std::to_string(players[0]->getScore()) + "\n", centerPileView->getID());
    // Cnsl::print(players[1]->name + ": " + std::to_string(players[1]->getScore()) + "\n\n", centerPileView->getID());

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

Player *EgyptianRatscrewGame::getCurrentPlayer() {
    Player *currentPlayer = players[currentPlayerIdx];
    assert(currentPlayer);
    return currentPlayer;
}

Player *EgyptianRatscrewGame::getLastPlayer(int playerIdx) {
    if (playerIdx < 0) { playerIdx = currentPlayerIdx; }
    int lastPlayerIdx = (playerIdx <= 0) ? players.size() - 1 : playerIdx - 1;
    return players[lastPlayerIdx];
}

bool EgyptianRatscrewGame::isGameDone() {
    for (int playerIdx = 0; playerIdx < players.size(); playerIdx++) {     
        Player *player = players[playerIdx];   
        assert(player);
        if (player->getScore() <= 0) {
            Player *winner = getLastPlayer(playerIdx);
            Cnsl::print(winner->name + " won! Great Job!");
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