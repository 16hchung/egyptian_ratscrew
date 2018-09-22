#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "console_handler.h"

class Player {
public:
    Player(std::string name);

    const std::string name;
    static const size_t maxNameLen = 20;

    void addCard(Card *card);
    void addCards(std::stack<Card *> &cardsToAdd);
    Card *getCard();

    int getScore(); // just number of cards in possession

private:
    std::deque<Card *> cards;
};

#endif