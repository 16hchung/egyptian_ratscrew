#ifndef BURN_CENTER_PILE_VIEW_H
#define BURN_CENTER_PILE_VIEW_H
#include "abstract_view.h"

class BurnCenterPileView : public CenterCardPileView {
public:
    BurnCenterPileView() : CenterCardPileView(ConsoleHandler::MainRight) {}
};

#endif