#ifndef ERS_GAME_H
#define ERS_GAME_H
#include "deck.h"
#include "center_pile.h"

// forward declarations
class MainCenterPileView;
class BurnCenterPileView;
class PlayerView;
class InstructionsView;

class EgyptianRatscrewGame {
public:
    EgyptianRatscrewGame();
    ~EgyptianRatscrewGame();

    void play();

private:
    bool playerSlappedCenter(int playerIdx);
    void cardDown();

    void checkWindowSize();
    bool isGameDone();
    void printIntro();
    void initPlayers();
    void initViews();
    void nextPlayerTurn();
    Player *getLastPlayer(int playerIdx = -1);
    Player *getCurrentPlayer();

    // Model
    std::string winnerName = "";
    bool shouldKillGame = false;

    Deck deck;
    CenterCardPile centerPile;
    std::vector<Player *> players;

    int currentPlayerIdx = 0;
    
    // Views
    MainCenterPileView *centerPileView   = nullptr;
    BurnCenterPileView *burnPileView     = nullptr;
    PlayerView         *player1View      = nullptr;
    PlayerView         *player2View      = nullptr;
    InstructionsView   *instructionsView = nullptr;
};

#endif