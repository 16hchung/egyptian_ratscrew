#include <string>
#include "card.h"

// Constructor
Card::Card(Suit suit, int rank) : suit(suit), rank(rank) {
}

std::string Card::get_suit() {
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

int Card::get_rank() {
    return rank;
}
