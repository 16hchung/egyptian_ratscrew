#include <ncurses.h>
#include <panel.h>
#include "console_handler.h"

bool ConsoleHandler::f_useNcurses = false;

ConsoleHandler::MoveType ConsoleHandler::waitForMove() {
    return ConsoleHandler::CardDown;
}

void ConsoleHandler::initWindow() {
    f_useNcurses = true;
    initscr();
    cbreak();
    noecho();
    clear();
    scrollok(stdscr, true);
}

void ConsoleHandler::closeWindow() {
    print("Press any key to exit game.\n");
    getch();
    endwin();
    f_useNcurses = false;
}

void ConsoleHandler::print(std::string str) {
    waddstr(stdscr, str.c_str());
}

std::string ConsoleHandler::getInput(std::string prompt) {
    print(prompt);
    return getString();
}

/*
Pulled from: https://stackoverflow.com/questions/26920261/read-a-string-with-ncurses-in-c
 */
std::string ConsoleHandler::getString() {
    std::string input;

    // let the terminal do the line editing
    nocbreak();
    echo();

    // this reads from buffer after <ENTER>, not "raw" 
    // so any backspacing etc. has already been taken care of
    int ch = getch();
    while ( ch != '\n' ) {
        input.push_back( ch );
        ch = getch();
    }

    // restore cbreak / echo settings 
    noecho();
    cbreak();
    return input;
}