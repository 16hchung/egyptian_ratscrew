#include "card.h"

// Constructor
Card::Card(Suit suit, int rank) : suit(suit), rank(rank) {}

std::string Card::toString() {
    return suitString()  + ", " + std::to_string(rank);
}

std::string Card::suitString() {
    switch (suit) {
    case Hearts:
        return "Hearts";
    case Spades:
        return "Spades";
    case Diamonds:
        return "Diamonds";
    case Clubs:
        return "Clubs";
    }
}
