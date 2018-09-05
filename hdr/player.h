#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"

class Player {
public:
    
    void addCard(Card *card);
    // void addCards(std::vector<Card *> &cards);
    // int get_score(); // just number of cards in possession
private:
    std::queue<Card *> cards;
};

#endif