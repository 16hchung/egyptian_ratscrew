#ifndef CONSOLE_H
#define CONSOLE_H
#include "common_hdrs.h"

struct ConsoleHandler {
public:
    enum MoveType { CardDown, Slap };

    static MoveType waitForMove();

    static void print(std::string str);
    static std::string getInput(std::string prompt = "");

    static void initWindow();
    static void closeWindow();

private:
    static std::string getString();

    static bool f_useNcurses;

};

#endif