#ifndef INSTRUCTIONS_VIEW_H
#define INSTRUCTIONS_VIEW_H
#include "abstract_view.h"
#include "center_pile.h"

class InstructionsView : public ViewBase {
public:
    InstructionsView();

    void printCredits(std::string winnerName = "");
    void printValidSlap(std::string playerName, CenterCardPile::SlapType slapType);
    void printInvalidSlap(std::string playerName);
    void printDefault();
    ConsoleHandler::MoveType printCountdownOver();

private:
    static const std::string defaultText;

    void waitForSpecificKey(ConsoleHandler::MoveType moveType, bool resetContent = true);
};


#endif