#include "deck.h"

Deck::Deck() {
    cards.reserve(Card::stdDeckCount); // pre-allocate memory for cards

    // iterate through possible ranks and suits and generate deck
    for (int rank = 1; rank <= Card::numRanks; ++rank) {
        for (int suitInt = 0; suitInt < Card::numSuits; ++suitInt) {
            Card::Suit suit = static_cast<Card::Suit>(suitInt);
            cards.emplace_back(suit, rank);
        }
    }
}

void Deck::deal(std::vector<Player *> &players) {
    // create and shuffle list of card indicies
    std::vector<int> cardIndices;
    cardIndices.reserve(Card::stdDeckCount);
    for (int i = 0; i < Card::stdDeckCount; i++) { cardIndices.emplace_back(i); }
    std::shuffle(cardIndices.begin(), cardIndices.end(), std::default_random_engine(std::random_device()()));

    // go through generated indices and deal evenly to players
    int numPlayers = players.size();
    for (int cardIdxIdx = 0, playerIdx = 0; 
         cardIdxIdx < Card::stdDeckCount; 
         cardIdxIdx++, playerIdx = (playerIdx + 1) % numPlayers) 
    {
        int cardIdx = cardIndices[cardIdxIdx];
        // pass pointer of card to player
        players[playerIdx]->addCard(&(cards[cardIdx]));
    }
}
