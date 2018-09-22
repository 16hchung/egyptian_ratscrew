#include "ers_game.h"
#include "console_handler.h"
#include "main_center_pile_view.h"
#include "burn_center_pile_view.h"
#include "player_view.h"
#include "instructions_view.h"

using Cnsl = ConsoleHandler;

EgyptianRatscrewGame::EgyptianRatscrewGame() {
    Cnsl::initWindow();
    printIntro();
    initPlayers();
    deck.deal(players);
    initViews();
}

EgyptianRatscrewGame::~EgyptianRatscrewGame() {
    instructionsView->printCredits(winnerName);
    for (Player *player : players) {
        delete player;
    }
    delete centerPileView;
    delete burnPileView;
    delete player1View;
    delete player2View;
    delete instructionsView;
    Cnsl::closeWindow();
}

void EgyptianRatscrewGame::play() {
    Cnsl::MoveType move = Cnsl::waitForMove(instructionsView->getID());
    while (!isGameDone() && move != Cnsl::QuitGame) {
        bool f_shouldQuit = false;
        switch (move) {
        case Cnsl::Player1Slap: case Cnsl::Player2Slap:
            playerSlappedCenter((int) move); // enum values represent player index
            break;
        case Cnsl::CardDown:
            cardDown();
            break;
        case Cnsl::Continue:
            break;
        case Cnsl::QuitGame:
        default:
            f_shouldQuit = true;
            break;
        }
        if (f_shouldQuit) { break; }
        move = Cnsl::waitForMove(instructionsView->getID());
    }
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
    assert(players.size() == 2);
    player1View = new PlayerView(Cnsl::SmallLeft,  players[0]->name, Cnsl::player1Key, players[0]->getScore());
    player2View = new PlayerView(Cnsl::SmallRight, players[1]->name, Cnsl::player2Key, players[1]->getScore());
    centerPileView   = new MainCenterPileView();
    burnPileView     = new BurnCenterPileView();
    instructionsView = new InstructionsView();
}

void EgyptianRatscrewGame::playerSlappedCenter(int playerIdx) {
    if (centerPile.numCards() <= 0) { return; } // if multiple slaps in a row, only process the first
    assert(0 <= playerIdx && playerIdx < players.size());
    Player *player = players[playerIdx];
    PlayerView *playerView = (playerIdx) ? player2View : player1View;
    assert(player);
    // determine if pile is slappable
    CenterCardPile::SlapType slap = centerPile.currentSlapType();
    if (slap == CenterCardPile::Invalid) {
        instructionsView->printInvalidSlap(player->name);
        Card *card = player->getCard();
        centerPile.burnCard(card);
        burnPileView->printCard(card);
    } else {
        instructionsView->printValidSlap(player->name, slap);
        centerPile.giveCardsToPlayer(player);
        currentPlayerIdx = playerIdx;
        centerPileView->clear();
        burnPileView->clear();
    }
    playerView->update(player->getScore());
    return;
}

void EgyptianRatscrewGame::cardDown() {
    Player *currentPlayer = getCurrentPlayer();
    PlayerView *currentPlayerView = (currentPlayerIdx) ? player2View : player1View;
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
    currentPlayerView->update(currentPlayer->getScore());
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
            winnerName = winner->name;
            return true;
        }
    }
    return false;
}
