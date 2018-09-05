#ifndef ERS_GAME_H
#define ERS_GAME_H
#include "deck.h"

class EgyptianRatscrewGame {
public:
    EgyptianRatscrewGame();
    ~EgyptianRatscrewGame();

    void printIntro();
    bool playerSlappedCenter(Player *player);
    bool isGameDone();

    int test = 0;

private:
    Deck deck;
    std::vector<Card *> centerPile;
    std::vector<Player *> players;
};

#endif