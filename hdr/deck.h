#ifndef DECK_H
#define DECK_H
#include "player.h"

class Deck {
public:
    // constructor/destructor
    Deck();
    static const int numCards = Card::numRanks * Card::numSuits;
    void deal(std::vector<Player *> &players);

private:
    std::vector<Card> cards;

};


#endif