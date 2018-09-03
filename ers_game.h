#ifndef ERS_GAME_H
#define ERS_GAME_H

class EgyptianRatscrewGame {
public:
    EgyptianRatscrewGame();
    ~EgyptianRatscrewGame();

    void printIntro();
    bool playerSlappedCenter(Player *player);
    bool isGameDone();
    
private:
    Deck *deck;
    std::vector<Card *> centerPile;
    std::vector<Player *> players;
}

#endif