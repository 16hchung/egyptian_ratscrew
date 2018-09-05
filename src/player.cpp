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

int Player::get_score() {
    return cards.size();
}

/* Helpful Debug Methods */

void Player::print() {
    std::cout << name << std::endl;
    for (Card *card : cards) {
        std::cout << card->toString() << std::endl;
    }
    std::cout << std::endl;
}