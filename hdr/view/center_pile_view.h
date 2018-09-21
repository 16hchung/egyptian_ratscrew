#ifndef CENTER_PILE_VIEW_H
#define CENTER_PILE_VIEW_H
#include "abstract_view.h"

class Card;

class CenterCardPileView: public ViewBase {
public:
    CenterCardPileView(ConsoleHandler::WindowPosition position) : ViewBase(position) {}

    void printCard(Card* card);
protected:
};

#endif