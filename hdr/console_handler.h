#ifndef CONSOLE_H
#define CONSOLE_H
#include "common_hdrs.h"

struct ConsoleHandler {
public:
    enum MoveType { CardDown, Player1Slap, Player2Slap, QuitGame };

    static MoveType waitForMove();

    static void print(std::string str);
    static std::string getInput(std::string prompt = "");

    static void initWindow();
    static void closeWindow();

private:
    static std::string getString();

    // flag to keep track of whether or not ncurses window is open 
    // (different printing/input method depending on whether window is open or not)
    static bool f_useNcurses;

    // Constants
    static const char player1Key = 'D';
    static const char player2Key = 'K';
    static const char cardDownKey = ' ';
};

#endif