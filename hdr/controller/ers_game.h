#ifndef ERS_GAME_H
#define ERS_GAME_H
#include "deck.h"
#include "center_pile.h"

class EgyptianRatscrewGame {
public:
    EgyptianRatscrewGame();
    ~EgyptianRatscrewGame();

    bool playerSlappedCenter(int playerIdx);
    void cardDown();
    bool isGameDone();

    // helpful debug methods, TODO: get rid of this
    void printPlayers();

private:
    void printIntro();
    void initPlayers();
    void nextPlayerTurn();
    Player *getLastPlayer();
    Player *getCurrentPlayer();

    Deck deck;
    CenterCardPile centerPile;
    std::vector<Player *> players;

    int currentPlayerIdx = 0;

};

#endif