#ifndef ERS_GAME_H
#define ERS_GAME_H
#include "deck.h"
#include "center_pile.h"

// forward declarations
class MainCenterPileView;
class BurnCenterPileView;

class EgyptianRatscrewGame {
public:
    EgyptianRatscrewGame();
    ~EgyptianRatscrewGame();

    void playerSlappedCenter(int playerIdx);
    void cardDown();
    bool isGameDone();

    // helpful debug methods, TODO: get rid of this
    void printPlayers();

private:
    void printIntro();
    void initPlayers();
    void initViews();
    void nextPlayerTurn();
    Player *getLastPlayer(int playerIdx = -1);
    Player *getCurrentPlayer();

    // Model
    Deck deck;
    CenterCardPile centerPile;
    std::vector<Player *> players;

    int currentPlayerIdx = 0;
    
    // Views
    MainCenterPileView *centerPileView;
    BurnCenterPileView *burnPileView;
};

#endif