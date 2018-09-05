#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "console_handler.h"

class Player {
public:
    Player(std::string name);

    const std::string name;

    void addCard(Card *card);
    void addCards(std::vector<Card *> &cardsToAdd);
    int get_score(); // just number of cards in possession

    // helpful debug methods
    void print();

private:
    std::deque<Card *> cards;
};

#endif