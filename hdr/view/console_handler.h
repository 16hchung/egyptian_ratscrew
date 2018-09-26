/**
 * console_handler.h
 * -----------------
 * class handling everything that needs to interface with ncurses. If ever need to change libraries,
 * only change this file. Handles keyboard input and windows
 */

#ifndef CONSOLE_H
#define CONSOLE_H
#include "common_hdrs.h"
#include <ncurses.h>

// For purposes of this game, there is only one console, so make everything static.
// This has a bunch of pointers/references that shouldn't be accessible elsewhere, though, so use
// struct instead of namespace

struct ConsoleHandler {
public:
    // once game starts, there are only four keys which trigger specific actions (moves), Misc
    // covers other keys
    enum MoveType { Player1Slap = 0, Player2Slap = 1, CardDown, QuitGame, Misc };
    // don't want any overlap between windows inside console, so use an enum to keep track of position
    enum WindowPosition { MainLeft, MainRight, Middle, SmallLeft, SmallRight };
    
    // Keys each player has to type to slap the central pile
    static const char player1Key   = 'D';
    static const char player2Key   = 'K';

    /** enables and sets up ncurses */
    static void initConsole();

    /** disables ncurses and resets original terminal settings */
    static void closeConsole();

    /**
     * like std::cin, determines if an ncurses window is open and if so, uses ncurses method for
     * getting string input, else uses std::cin
     * @param  len    max character length of input
     * @param  prompt to ask user
     * @return        input from user
     */
    static std::string getInput(size_t len, std::string prompt = "");

    /**
     * waits for user to type actionable key
     * @param  windowID         id returned from newWindow
     * @param  incorrectKeyText what to display if user types unrecognized key
     * @param  acceptMisc       if true, will return as soon as user types any key, else will wait
     *                          for user to type actionable (not Misc)
     * @return                  action that should take place after user's key press
     */
    
    static MoveType waitForMove(int windowID = -1, std::string incorrectKeyText = "", bool acceptMisc = false);
    
    /**
     * like std::cout, determines correct way to display text on screen
     * @param str      string to print
     * @param windowId id of window returned from newWindow
     */
    static void print(std::string str, int windowId = -1);

    /**
     * creates new window (a rectangular area within console, any text written to window won't go
     * outside of the window's bounds)
     * @param  position    position of window
     * @param  windowLabel some windows require label to show what window is for
     * @return             window ID -- this should be passed to any future calls to window handlers
     */
    static int newWindow(WindowPosition position, std::string windowLabel = "");
    
    /**
     * clears contents of window (label stays in place)
     * @param windowId id of window that was returned from call to newWindow
     */
    static void clearWindow(int windowId = -1);
    
    /**
     * gets number of lines in console (ie height)
     * @return number of lines
     */
    static int getTotalNLines(); // lazy initialize
    
    /**
     * gets number of columns in console (ie width)
     * @return [description]
     */
    static int getTotalNCols();

private:
    // don't want content to overwrite characters that make up window border, so have separate border
    // window underneath content window
    static std::vector<WINDOW *> borderWindows;
    static std::vector<WINDOW *> contentWindows;
    // used to ensure we don't have overlapping windows
    static std::set<WindowPosition> occupiedPositions;
    // flag to keep track of whether or not ncurses window is open 
    // (different printing/input method depending on whether window is open or not)
    static bool f_useNcurses;
    // total number of lines (height) and columns (width) in console
    static int totalNLines;
    static int totalNCols;

    // Constants
    // keyboard keys for moves
    static const char player1Key_l = 'd';
    static const char player2Key_l = 'k';
    static const char quitKey      = 'Q';
    static const char quitKey_l    = 'q';
    static const char cardDownKey  = ' ';

    /**
     * converts more general position (left, right, smaller left, etc) into coordinates
     * @param position desired position for window
     * @param nlines   output param
     * @param ncols    output param
     * @param x        output param
     * @param y        output param
     */
    static void coordsForPosition(WindowPosition position, int &nlines, int &ncols, int &x, int &y);
    
    /**
     * checks if there is already a window in the requested position
     * @param  position window position
     * @return          true if occupied, else false
     */
    
    static bool isPositionOccupied(WindowPosition position);
    
    /**
     * sets a window position
     * @param position   window position
     * @param isOccupied if true, sets position to occupied, else sets to empty
     */
    static void setOccupiedPosition(WindowPosition position, bool isOccupied);

    /** helper function for getInput */
    static std::string getString(size_t len);

};

#endif