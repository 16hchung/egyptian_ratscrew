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
    if (f_useNcurses) {
        waddstr(stdscr, str.c_str());
    } else {
        std::cout << str;
    }
}

std::string ConsoleHandler::getInput(std::string prompt) {
    print(prompt);
    return getString();
}


std::string ConsoleHandler::getString() {
    std::string input;
    if (f_useNcurses) {
        // Pulled from following link...
        // https://stackoverflow.com/questions/26920261/read-a-string-with-ncurses-in-c

        // let the terminal do the line editing
        nocbreak();
        echo();
        int ch = getch();
        while ( ch != '\n' ) {
            input.push_back( ch );
            ch = getch();
        }
        // restore cbreak / echo settings 
        noecho();
        cbreak();
    } else {
        std::cin >> input;
    }
    return input;
}