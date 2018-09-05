#ifndef CONSOLE_H
#define CONSOLE_H

struct ConsoleHandler {
    enum MoveType { CardDown, Slap };

    static MoveType waitForMove();

    static void initWindow();
    static void closeWindow();
    static void playGame();
};

#endif