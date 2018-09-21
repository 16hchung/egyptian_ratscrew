#ifndef CARD_H
#define CARD_H
#include "common_hdrs.h"

class Card {
public:
    // types
    enum Suit { Hearts, Spades, Clubs, Diamonds};
    enum class Rank {
        Ace   = 'A',
        Two   = '2',
        Three = '3',
        Four  = '4',
        Five  = '5',
        Six   = '6',
        Seven = '7', 
        Eight = '8',
        Nine  = '9',
        Ten   = '1',
        Jack  = 'J',
        Queen = 'Q',
        King  = 'K',
    };

    // helpful constants
    static const int numSuits = 4;
    static const int numRanks = 13;
    static const std::vector<Rank> possibleRanks;

    // constructor
    Card(Suit suit, Rank rank);


    // getters
    std::string toString(); // have this here so we can lazy instantiate printable representation
    std::string suitString();

    // basic properties
    const Suit suit;
    const Rank rank;

private:
    // Helper vars and functions for generating string representation
    std::string generateStringRepresentation();

    std::string stringRepresentation = "";

    static const std::string spadesTemplate;
    static const std::string heartsTemplate;
    static const std::string diamondsTemplate;
    static const std::string clubsTemplate;

    static const std::string templatePlaceholder;

};

#endif