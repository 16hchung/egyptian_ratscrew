#include <vector>
#include <algorithm>
#include "deck.h"

Deck::Deck() {
    cards.reserve(numCards); // pre-allocate memory for cards

    // iterate through possible ranks and suits and generate deck
    for (int rank = 1; rank <= Card::numRanks; ++rank) {
        for (int suitInt = 0; suitInt < Card::numSuits; ++suitInt) {
            Card::Suit suit = static_cast<Card::Suit>(suitInt);
            cards.emplace_back(suit, rank);
        }
    }
}

Deck::~Deck() {
}

void Deck::deal(std::vector<Player *> &players) {
    // create and shuffle list of card indicies
    std::vector<int> cardIndices;
    cardIndices.reserve(numCards);
    for (int i = 0; i < numCards; i++) { cardIndices.emplace_back(i); }
    std::random_shuffle(cardIndices.begin(), cardIndices.end());

    // go through generated indices and deal evenly to players
    int numPlayers = players.size();
    for (int cardIdxIdx = 0, playerIdx = 0; 
         cardIdxIdx < numCards; 
         cardIdxIdx++, playerIdx = (playerIdx + 1) % numPlayers) 
    {
        int cardIdx = cardIndices[cardIdxIdx];
        // pass pointer of card to player
        players[playerIdx]->addCard(&(cards[cardIdx]));
    }
}
