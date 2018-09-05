#include "player.h"

Player::Player(std::string name) : name(name) {}

void Player::addCard(Card *card) {
    cards.push_front(card);
}

void Player::addCards(std::vector<Card *> &cardsToAdd) {
    // iterate through cards and add to member queue
    // stack of cards gets added to *bottom* of player's hand, so enqueue in reverse order 
    for (int i = cardsToAdd.size() - 1; i > 0; ++i) {
        cards.push_front(cardsToAdd[i]);
    }
}

int Player::getScore() {
    return cards.size();
}

/* Helpful Debug Methods */

void Player::print() {
    ConsoleHandler::print(name + "\n");
    for (Card *card : cards) {
        ConsoleHandler::print(card->toString() + "\n");
    }
    ConsoleHandler::print("\n");
}