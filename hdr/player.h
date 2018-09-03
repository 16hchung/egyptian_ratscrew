#ifndef CARD_H
#define CARD_H value

class Player {
public:
    
    void addCard(Card *card);
    // void addCards(std::vector<Card *> &cards);
    // int get_score(); // just number of cards in possession
private:
    std::queue<Card *> cards = {};
};

#endif