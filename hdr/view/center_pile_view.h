/**
 * center_pile_view.h
 * ------------------
 * class handling section of console which can display cards
 */
#ifndef CENTER_PILE_VIEW_H
#define CENTER_PILE_VIEW_H
#include "abstract_view.h"

class Card;

class CenterCardPileView: public ViewBase {
public:
    /**
     * @param position where to position window
     * @param label    text to always display at top of view
     */
    CenterCardPileView(ConsoleHandler::WindowPosition position, std::string label)
    : ViewBase(position, label) {}

    /**
     * display card in view using ascii art
     * @param card   pointer to card object
     */
    void printCard(Card* card);

protected:
private:
};

#endif