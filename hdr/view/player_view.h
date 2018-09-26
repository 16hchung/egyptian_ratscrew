/**
 * player_view.h
 * -------------
 * class handling section of console showing player stats like # of cards, name, etc.
 */

#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H
#include "abstract_view.h"

class PlayerView : public ViewBase {
public:
    /**
     * @param position:  section of the console to put the window in
     * @param name:      player name
     * @param slapChar:  key that player has to type to slap central pile
     * @param cardCount: number of cards the player starts off with
     */
    PlayerView(ConsoleHandler::WindowPosition position, std::string name, char slapChar, int cardCount);

    /**
     * called to change text displaying player's card count
     * @param cardCount: new card count
     */
    void update(int cardCount);

private:
    // key that player has to type to slap central pile
    const char        slapChar;
    const std::string playerName;
};

#endif