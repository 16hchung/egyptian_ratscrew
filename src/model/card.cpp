#include "card.h"

const std::vector<Card::Rank> Card::possibleRanks = { Card::Rank::Ace, Card::Rank::Two, 
    Card::Rank::Three, Card::Rank::Four, Card::Rank::Five, Card::Rank::Six, Card::Rank::Seven, 
    Card::Rank::Eight, Card::Rank::Nine, Card::Rank::Ten, Card::Rank::Jack, 
    Card::Rank::Queen, Card::Rank::King };

// Constructor
Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank) {
    stringID = suitString() + static_cast<char>(rank);
}

std::string Card::toString() {
    return suitString()  + ", " + static_cast<char>(rank);
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

std::string Card::getStringID() {
    return stringID;
}