#include "center_pile.h"

using Rank = Card::Rank;

void CenterCardPile::addCard(Card *card, bool &out_startedNewCountdown, // output params
                                         bool &out_wasInCountdown, 
                                         bool &out_countDownFinished)
{
    assert(card);
    Card *oldTop = (cards.empty()) ? nullptr : cards.top();
    cards.push(card);
    // update center pile pointers
    if (bottom == nullptr) {
        assert(cards.size() == 1);
        bottom = card;
    }
    thirdToTop = secondToTop;
    secondToTop = oldTop;

    // Handle face card countdown...
    int newCountdown = faceCardCountdownForRank(card->rank);
    out_startedNewCountdown = newCountdown > 0;
    out_wasInCountdown = faceCardCountdown > 0;
    // if we have a new face card, or if we're not currently in the middle of a countdown, reset
    if (out_startedNewCountdown || !out_wasInCountdown) {
        faceCardCountdown = newCountdown;
        out_countDownFinished = false;
    } else {
        faceCardCountdown--;
        out_countDownFinished = faceCardCountdown <= 0;
    }
}

void CenterCardPile::addCard(Card * card) {
    bool dummy_startedNewCountdown, dummy_wasInCountdown, dummy_finishedCountdown;
    if (!card) { return; }
    addCard(card, dummy_startedNewCountdown, dummy_wasInCountdown, dummy_finishedCountdown);
}

void CenterCardPile::burnCard(Card *card) {
    if (!card) { return; }
    burnPile.push(card);
}

void CenterCardPile::giveCardsToPlayer(Player *player) {
    assert(player);
    player->addCards(cards);
    player->addCards(burnPile); // burn pile get's put below center pile in real-life game play
    reset();
}

CenterCardPile::SlapType CenterCardPile::currentSlapType() {
    // can't have a slap with just one card
    if (cards.size() <= 1 || !secondToTop) { 
        return Invalid;
    }
    assert(secondToTop && bottom);
    Card *top = cards.top();
    Rank topRank = top->rank;
    Rank secondRank = secondToTop->rank; // no line for thirdRank because might be null
    Rank bottomRank = bottom->rank;
    SlapType slap = Invalid; // start out assuming there is no slap
    // Check for 2-card slaps...
    if (topRank == secondRank) {
        slap = Double;
    } else if (cardPairHasRanks(top, secondToTop, Rank::King, Rank::Queen)) {
        slap = Marriage;
    } else if (cardPairHasRanks(top, secondToTop, Rank::King, Rank::Jack)) {
        slap = Rainbow;
    } else if (cardPairHasRanks(top, secondToTop, Rank::Queen, Rank::Jack)) {
        slap = Affair;
    // Check for 3-card slaps...
    } else if (thirdToTop && topRank == thirdToTop->rank) {
        slap = Sandwich;
    } else if (topRank == bottomRank) {
        slap = TopBottom;
    }    
    return slap;
}

void CenterCardPile::reset() { 
    faceCardCountdown = 0;
    bottom = secondToTop = thirdToTop = nullptr;
}

int CenterCardPile::faceCardCountdownForRank(Card::Rank rank) {
    // If face card put down, next player has `n` chances to put down another face card
    // For Jack: `n` = 1, Queen:    `n` = 2, King:     `n` = 3, Ace:      `n` = 4
    switch (rank) {
    case Rank::Ace:
        return 4;
    case Rank::King:
        return 3;
    case Rank::Queen:
        return 2;
    case Rank::Jack:
        return 1;
    default:
        return 0; // no countdown for non-face cards
    }
}

bool CenterCardPile::cardPairHasRanks(Card *card1, Card *card2, Rank rank1, Rank rank2) {
    return (card1->rank == rank1 && card2->rank == rank2) 
        || (card1->rank == rank2 && card2->rank == rank1);
}

int CenterCardPile::numCards() {
    return cards.size() + burnPile.size();
}