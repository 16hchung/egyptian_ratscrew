#ifndef CENTER_PILE_VIEW_H
#define CENTER_PILE_VIEW_H
#include "abstract_view.h"

class Card;

class CenterCardPileView: public ViewBase {
public:
    CenterCardPileView(ConsoleHandler::WindowPosition position) : ViewBase(position) {}

    void printCard(Card* card);

protected:
private:
    // lazily instantiate map from card "ID" (string representation) to printable card string,
    // since using regex to generate, which can slow things down
    static std::map<std::string, std::string> cardIDToPrintableString;
};

#endif