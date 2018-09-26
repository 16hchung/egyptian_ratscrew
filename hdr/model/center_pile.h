/**
 * center_pile.h
 * -------------
 * model class for central pile of cards
 */

#ifndef CENTER_PILE_H
#define CENTER_PILE_H
#include "player.h"

class CenterCardPile {
public:
    // If central pile is not slapable, then slap type is invalid, else it's set to one of the other
    // enum values
    enum SlapType { Invalid, Double, Sandwich, TopBottom, Marriage, Rainbow, Affair, Divorce };

    /**
     * adds card to central pile 
     * @param card: card to add
     */
    void addCard(Card *card); // override because can't set default value for param passed by ref

    /**
     * same as above method, but with some output parameters
     * @param out_startedNewCountdown true if card is a face card
     * @param out_wasInCountdown      true if, before card was placed down, face card countdown was
     *                                in progress
     * @param out_countDownFinished   true if face card countdown ran out
     */
    void addCard(Card *card, bool &out_startedNewCountdown,
                             bool &out_wasInCountdown,
                             bool &out_countDownFinished);

    /**
     * add card to burn pile
     * @param card
     */
    void burnCard(Card *card);

    /**
     * deal all cards in both central and burn piles to player
     * @param player
     */
    void giveCardsToPlayer(Player *player);

    /**
     * determines if central pile is slappable and, if so, what pattern makes it so
     * @return slap type
     */
    SlapType currentSlapType();

    /**
     * count of cards in both burn and central piles
     * @return number of cards
     */
    int numCards();
    
private:
    // keep cards and burn pile separatefor clarity (also so that we don't change bottom card for slaps)
    std::stack<Card *> cards;
    std::stack<Card *> burnPile;

    // pointers to lower in center pile stack, since stack only lets us see the top card
    // used to determine slap type, if any
    Card *bottom = nullptr;
    Card *secondToTop = nullptr;
    Card *thirdToTop = nullptr;

    // keeps track of whether or not we're in a face card countdown and how many chance we have
    // before it runs out
    int faceCardCountdown = 0;

    // resets central pile after cards delt to player
    void reset();

    // class helper functions
    
    /**
     * determines how many chances next player has to put down another face card after this face card
     * @param  rank (of current face card)
     * @return      number of chances
     */
    static int faceCardCountdownForRank(Card::Rank rank);

    /**
     * given pair of cards, and pair of ranks, determines if first card has first rank and second
     * card has second rank or vice versa
     * @param  card1  pair of cards
     * @param  card2  ^
     * @param  rank1  pair of ranks
     * @param  rank2  ^
     * @return       true if pair of cards contains ranks
     */
    static bool cardPairHasRanks(Card *card1, Card *card2, Card::Rank rank1, Card::Rank rank2);
};


#endif