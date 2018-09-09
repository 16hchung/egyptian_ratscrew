#ifndef CENTER_PILE_H
#define CENTER_PILE_H
#include "player.h"

class CenterCardPile {
public:
    enum SlapType { Invalid, Double, Sandwich, TopBottom, Marriage, Rainbow, Affair, Divorce };

    // instance methods
    void addCard(Card *card); // override because can't set default value for param passed by ref
    void addCard(Card *card, bool &out_startedNewCountdown,
                             bool &out_wasInCountdown,
                             bool &out_countDownFinished);
    void burnCard(Card *card);
    void giveCardsToPlayer(Player *player);
    SlapType currentSlapType();

private:
    std::stack<Card *> cards;
    std::stack<Card *> burnPile;

    // pointers to lower in center pile stack, since stack only lets us see the top card
    Card *bottom = nullptr;
    Card *secondToTop = nullptr;
    Card *thirdToTop = nullptr;

    int faceCardCountdown = 0;

    void reset();

    // class helper functions
    static int faceCardCountdownForRank(Card::Rank rank);
    static bool cardPairHasRanks(Card *card1, Card *card2, Card::Rank rank1, Card::Rank rank2);
};


#endif