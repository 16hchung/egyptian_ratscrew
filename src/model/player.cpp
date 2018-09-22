#include "player.h"

Player::Player(std::string name) : name(name) {}

void Player::addCard(Card *card) {
    cards.push_front(card);
}

void Player::addCards(std::stack<Card *> &cardsToAdd) {
    // stack of cards gets added to *bottom* of player's hand, so enqueue in order that cards
    // get popped off the stack 
    while (!cardsToAdd.empty()) {
        cards.push_front(cardsToAdd.top());
        cardsToAdd.pop();
    }
}

Card * Player::getCard() {
    if (cards.empty()) { return nullptr; }
    Card *card = cards.back();
    cards.pop_back();
    return card;
}

int Player::getScore() {
    return cards.size();
}