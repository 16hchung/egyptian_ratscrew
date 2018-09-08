#ifndef ERS_GAME_H
#define ERS_GAME_H
#include "deck.h"

class EgyptianRatscrewGame {
public:
    enum SlapType { Invalid, Double, Sandwich, TopBottom, Marriage, Rainbow, Affair, Divorce };

    EgyptianRatscrewGame();
    ~EgyptianRatscrewGame();

    bool playerSlappedCenter(int playerIdx);
    void cardDown();
    bool isGameDone();

    // helpful debug methods
    void printPlayers();

private:
    void printIntro();
    void initPlayers();
    int faceCardCountdownForRank(Card::Rank rank);
    void setToNextPlayer();
    Player *getLastPlayer();
    void addToCenterPile(Card *card);
    bool cardPairHasRanks(Card *card1, Card *card2, Card::Rank rank1, Card::Rank rank2);
    void resetCenterPile();

    SlapType currentSlapType();

    Deck deck;
    std::stack<Card *> centerPile;
    std::vector<Player *> players;

    int currentPlayerIdx = 0;
    int faceCardCountdown = 0;

    // pointers to lower in center pile stack, since stack only lets us see the top card
    Card *bottom = nullptr;
    Card *secondToTop = nullptr;
    Card *thirdToTop = nullptr;
};

#endif