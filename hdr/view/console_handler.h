#ifndef CONSOLE_H
#define CONSOLE_H
#include "common_hdrs.h"
#include <ncurses.h>

// For purposes of this game, there is only one console, so make everything static
// Have a bunch of pointers/references that shouldn't be accessible elsewhere, though, so use
// struct instead of namespace
struct ConsoleHandler {
public:
    enum MoveType { Player1Slap = 0, Player2Slap = 1, CardDown, QuitGame, Misc };
    enum WindowPosition { CenterLeft, CenterRight, Bottom, Left, Right };
    
    /* Keyboard related... */
    static MoveType waitForMove();
    static std::string getInput(size_t len, std::string prompt = "");

    /* Window related... */
    static int newWindow(WindowPosition position);

    /* Both window and keyboard related... */
    static void initWindow();
    static void closeWindow(bool prompt = true);
    static void print(std::string str, int windowId = -1);

private:
    static std::vector<WINDOW *> windows;
    static std::set<WindowPosition> occupiedPositions;
    // flag to keep track of whether or not ncurses window is open 
    // (different printing/input method depending on whether window is open or not)
    static bool f_useNcurses;

    /* Window helpers... */
    static void coordsForPosition(WindowPosition position, int &nlines, int &ncols, int &x, int &y);
    static bool isPositionOccupied(WindowPosition position);
    static void setOccupiedPosition(WindowPosition position, bool isOccupied);

    /* Keyboard helpers... */
    static std::string getString(size_t len);

    // Constants
    static const char player1Key   = 'D';
    static const char player1Key_l = 'd';
    static const char player2Key   = 'K';
    static const char player2Key_l = 'k';
    static const char quitKey      = 'Q';
    static const char quitKey_l    = 'q';
    static const char cardDownKey  = ' ';
};

#endif