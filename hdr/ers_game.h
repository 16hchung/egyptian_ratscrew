#ifndef ERS_GAME_H
#define ERS_GAME_H
#include "deck.h"

class EgyptianRatscrewGame {
public:
    EgyptianRatscrewGame();
    ~EgyptianRatscrewGame();

    bool playerSlappedCenter(Player *player);
    bool isGameDone();

    // helpful debug methods
    void printPlayers();

private:
    void printIntro();
    void initPlayers();

    Deck deck;
    std::vector<Card *> centerPile;
    std::vector<Player *> players;
};

#endif