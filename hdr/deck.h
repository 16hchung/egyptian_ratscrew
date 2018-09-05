#ifndef DECK_H
#define DECK_H
#include <vector>
#include "player.h"

class Deck {
public:
    // constructor/destructor
    Deck();
    ~Deck();

    void deal(std::vector<Player *> &players);

private:
    std::vector<Card> cards;

    static const int numCards = 52; //Card::numSuits * Card::numRanks;
};


#endif