#include "player_view.h"

PlayerView::PlayerView(ConsoleHandler::WindowPosition position, std::string name, char slapChar, int cardCount)
                      : ViewBase(position), playerName(name), slapChar(slapChar)
{
    update(cardCount);
}


void PlayerView::update(int cardCount) {
    clear();
    const std::string underline(playerName.size(), '-');
    ConsoleHandler::print(playerName + "\n", getID());
    ConsoleHandler::print(underline + "\n\n",  getID());
    ConsoleHandler::print(std::to_string(cardCount) + " cards\n\n",  getID());
    ConsoleHandler::print("Press " + std::string(1, slapChar) + " to slap",  getID());
}