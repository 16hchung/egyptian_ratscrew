#include "ers_game.h"
#include "console_handler.h"
#include "main_center_pile_view.h"
#include "burn_center_pile_view.h"
#include "player_view.h"
#include "instructions_view.h"
#include "intro_helper.h"

using Cnsl = ConsoleHandler;

EgyptianRatscrewGame::EgyptianRatscrewGame() {
    Cnsl::initConsole();
    initPlayers();
    checkWindowSize();
    if (shouldKillGame) { return; }
    printIntro();
    deck.deal(players);
    initViews();
}

EgyptianRatscrewGame::~EgyptianRatscrewGame() {
    for (Player *player : players) {
        delete player;
    }
    if (!shouldKillGame) {
        instructionsView->printCredits(winnerName);
        delete centerPileView;
        delete burnPileView;
        delete player1View;
        delete player2View;
        delete instructionsView;
    }
    Cnsl::closeConsole();
}

void EgyptianRatscrewGame::checkWindowSize() {
    // hard-coded constants
    const int minNumLines = 30;
    const int standardMinNumCols = 74;
    // width depends on player names
    if (players.size() != 2) {
        throw std::runtime_error("Trying to check window size before initlializing players.");
    }
    const int minNumCols = std::max(standardMinNumCols,
                                    (int) (players[0]->name.size() + players[0]->name.size() + 5));

    int numLines = Cnsl::getTotalNLines();
    int numCols = Cnsl::getTotalNCols();
    if (numLines < minNumLines || numCols < minNumCols) {
        shouldKillGame = true;
        Cnsl::print("Console window is too small to play. Please maximize (or reduce font size) "
                    "and run again. We'll exit this game now. Press any key to continue.");
        Cnsl::waitForMove(-1, "", true);
    }
}

void EgyptianRatscrewGame::printIntro() {
    const std::string yes   = "Y";
    const std::string yes_l = "y";
    const std::string no    = "N";
    const std::string no_l  = "n";

    Cnsl::print("Welcome to Egyptian Ratscrew!\n");
    std::string yesOrNo = "";
    while (yesOrNo != yes && yesOrNo != yes_l && yesOrNo != no && yesOrNo != no_l) {
        yesOrNo = Cnsl::getInput(1, "Want some instructions on how to play? (Y/N) ");
        Cnsl::print("\n");
    }
    if (yesOrNo == yes || yesOrNo == yes_l) {
        if (players.size() != 2) {
            throw std::runtime_error("Trying to print intro before initlializing players.");
        }
        IntroHelper::goThroughIntro(players[0]->name, players[1]->name);
    }
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

void EgyptianRatscrewGame::play() {
    if (shouldKillGame) { return; }
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
        case Cnsl::QuitGame:
        default:
            f_shouldQuit = true;
            break;
        }
        if (f_shouldQuit) { break; }
        move = Cnsl::waitForMove(instructionsView->getID());
    }
}

bool EgyptianRatscrewGame::playerSlappedCenter(int playerIdx) {
    if (centerPile.numCards() <= 0) { return false; } // if multiple slaps in a row, only process the first
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
    return slap != CenterCardPile::Invalid;
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
    // otherwise see if player is going to slap and handle accordingly
    Cnsl::MoveType nextMove = instructionsView->printCountdownOver();
    bool shouldLastPlayerGetCenterPile = true;
    if (nextMove != Cnsl::CardDown) {
        shouldLastPlayerGetCenterPile = !playerSlappedCenter((int) nextMove);
    }
    if (shouldLastPlayerGetCenterPile) {
        Player *lastPlayer = getLastPlayer();
        assert(lastPlayer);
        centerPile.giveCardsToPlayer(lastPlayer);
        centerPileView->clear();
        burnPileView->clear();
        player1View->update(players[0]->getScore());
        player2View->update(players[1]->getScore());
        nextPlayerTurn();

    }
    instructionsView->printDefault();
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
