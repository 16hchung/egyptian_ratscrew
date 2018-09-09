#ifndef CONSOLE_H
#define CONSOLE_H
#include "common_hdrs.h"
#include <ncurses.h>
#include <panel.h>

// For purposes of this game, there is only one console, so make everything static
// Have a bunch of pointers/references that shouldn't be accessible elsewhere, though, so use
// struct instead of namespace
struct ConsoleHandler {
public:
    enum MoveType { Player1Slap = 0, Player2Slap = 1, CardDown, QuitGame, Misc };

    static MoveType waitForMove();

    static void print(std::string str);
    static std::string getInput(size_t len, std::string prompt = "");

    static void initWindow();
    static void closeWindow(bool prompt = true);

private:
    std::vector<WINDOW *> windows;
    // flag to keep track of whether or not ncurses window is open 
    // (different printing/input method depending on whether window is open or not)
    static bool f_useNcurses;

    // helper functions
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