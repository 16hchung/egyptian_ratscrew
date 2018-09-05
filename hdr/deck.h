#ifndef DECK_H
#define DECK_H
#include "player.h"

class Deck {
public:
    // constructor/destructor
    Deck();
    ~Deck();

    void deal(std::vector<Player *> &players);

private:
    std::vector<Card> cards;

    static const int numCards = Card::numSuits * Card::numRanks;
};


#endif