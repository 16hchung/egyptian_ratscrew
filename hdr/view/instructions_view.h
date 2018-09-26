/**
 * instructions_view.h
 * -------------------
 * class handling section of console showing instructions (like keys to press) based on
 * state of the egyptia ratscrew game
 */

#ifndef INSTRUCTIONS_VIEW_H
#define INSTRUCTIONS_VIEW_H
#include "abstract_view.h"
#include "center_pile.h"

class InstructionsView : public ViewBase {
public:
    InstructionsView();

    /**
     * lets players know that there was valid slap
     * @param playerName name of player who made valid slap
     * @param slapType   type of pattern that makes central pile slappable
     */
    void printValidSlap(std::string playerName, CenterCardPile::SlapType slapType);

    /**
     * lets players know that there was invalid slap
     * @param playerName name of player who made invalid slap
     */
    void printInvalidSlap(std::string playerName);
    
    /**
     * default text lists keys to put card down and quit
     */
    void printDefault();

    /**
     * at end of ers game, prints credits for ASCII art for cards
     * @param winnerName name of winner
     */
    void printCredits(std::string winnerName = "");
    ConsoleHandler::MoveType printCountdownOver();

private:
    static const std::string defaultText;

    /**
     * waits for users to press specific key and keep prompting until user gives correct key
     * @param moveType     type of key to wait for
     * @param resetContent reset content to default after desired key has been pressed
     */
    void waitForSpecificKey(ConsoleHandler::MoveType moveType, bool resetContent = true);
};


#endif