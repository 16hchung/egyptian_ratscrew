#ifndef DECK_H
#define DECK_H
#include "player.h"

class Deck {
public:
    // constructor/destructor
    Deck();

    void deal(std::vector<Player *> &players);

private:
    std::vector<Card> cards;

};


#endif