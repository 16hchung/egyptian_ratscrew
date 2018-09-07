#ifndef ERS_GAME_H
#define ERS_GAME_H
#include "deck.h"

class EgyptianRatscrewGame {
public:
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

    Deck deck;
    std::stack<Card *> centerPile;
    std::vector<Player *> players;

    int currentPlayerIdx = 0;
    int faceCardCountdown = 0;

};

#endif