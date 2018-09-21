#include "center_pile_view.h"
#include "card.h"


void CenterCardPileView::printCard(Card* card) {
    ConsoleHandler::print(card->toString() + "\n", getID());    
}
