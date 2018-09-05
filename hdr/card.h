
#ifndef CARD_H
#define CARD_H
#include <string>

class Card {
public:
    // types
    enum Suit { Hearts, Spades, Clubs, Diamonds};

    // helpful constants
    static const int numSuits = 4;
    static const int numRanks = 13;

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