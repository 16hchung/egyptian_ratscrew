/**
 * deck.h
 * ------
 * model class handling card deck
 */

#ifndef DECK_H
#define DECK_H
#include "player.h"

class Deck {
public:
    Deck();

    // total number of cards in a standard deck
    static const int numCards = Card::numRanks * Card::numSuits;

    /**
     * deals all 52 cards in deck to players evenly
     * @param players vector of players
     */
    void deal(std::vector<Player *> &players);

private:
    std::vector<Card> cards;

};


#endif