
#ifndef CARD_H
#define CARD_H
#include "common_hdrs.h"

class Card {
public:
    // types
    enum Suit { Hearts, Spades, Clubs, Diamonds};

    // helpful constants
    static const int numSuits = 4;
    static const int numRanks = 13;
    static const int stdDeckCount = numSuits * numRanks;


    // constructor
    Card(Suit suit, int rank);

    // getters
    std::string get_suit();
    int get_rank();

private:
    // basic properties
    const Suit suit;
    const int rank;

};

#endif