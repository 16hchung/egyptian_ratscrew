#include "player.h"

void Player::addCard(Card *card) {
    cards.push(card);
}

void Player::addCards(std::vector<Card *> &cardsToAdd) {
    // iterate through cards and add to member queue
    // stack of cards gets added to *bottom* of player's hand, so enqueue in reverse order 
    for (int i = cardsToAdd.size() - 1; i > 0; ++i) {
        cards.push(cardsToAdd[i]);
    }
}

int Player::get_score() {
    return cards.size();
}