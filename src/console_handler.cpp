#include <ncurses.h>
#include <panel.h>
#include "console_handler.h"

ConsoleHandler::MoveType ConsoleHandler::waitForMove() {
    return CardDown;
}

void ConsoleHandler::initWindow() {
    initscr();
    cbreak();
    noecho();
}

void ConsoleHandler::closeWindow() {
    endwin();
}
