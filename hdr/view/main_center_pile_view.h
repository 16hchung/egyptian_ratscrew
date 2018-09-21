#ifndef MAIN_PILE_H
#define MAIN_PILE_H
#include "center_pile_view.h"

class MainCenterPileView : public CenterCardPileView {
public:
    MainCenterPileView() : CenterCardPileView(ConsoleHandler::MainLeft) {}
private:
};

#endif