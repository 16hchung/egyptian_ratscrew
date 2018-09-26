/**
 * player.h
 * --------
 * model class handling data and actions of players
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "console_handler.h"

class Player {
public:
    /**
     * @param name  name of player
     */
    Player(std::string name);

    const std::string name;
    // to avoid overflow (ncurses is a c library), enforce max name length
    static const size_t maxNameLen = 20;

    /**
     * adds card to top of player's hand
     * @param card card to add
     */
    void addCard(Card *card);

    /**
     * adds multiple cards to bottom of player's hand (cards at top of stack get put into bottom
     * of hand first)
     * @param cardsToAdd stack of cards
     */
    void addCards(std::stack<Card *> &cardsToAdd);

    /**
     * gets top card and removes from player's hand
     * @return top card on player's hand
     */
    Card *getCard();

    /**
     * returns number of cards in player's hand
     */
    int getScore();

private:
    // cards in player's hand
    std::deque<Card *> cards;
};

#endif