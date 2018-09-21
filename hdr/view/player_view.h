#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H
#include "abstract_view.h"

class PlayerView : public ViewBase {
public:
    PlayerView(ConsoleHandler::WindowPosition position, std::string name, char slapChar, int cardCount);

    void update(int cardCount);

private:
    const std::string playerName;
    const char slapChar;
};

#endif