#include <ncurses.h>
#include <panel.h>
#include "console_handler.h"

bool ConsoleHandler::f_useNcurses = false;

ConsoleHandler::MoveType ConsoleHandler::waitForMove() {
    const int maxTries = 10;
    for (int i = 0; i < maxTries; ++i) {
        char c = getch();
        switch (c) {
        case player1Key: case player1Key_l:
            return Player1Slap;
        case player2Key: case player2Key_l:
            return Player2Slap;
        case cardDownKey:
            return CardDown;
        case quitKey: case quitKey_l:
            return QuitGame;
        default:
            print("I don't recognize that key. \n");
            print("Press D (player 1 slap), K (player 2 slap), Space (card down), or Q (quit).\n");
        }
    }
    print("That was 10 unrecognized key presses. Quitting game.\n");
    return QuitGame;
}

void ConsoleHandler::initWindow() {
    f_useNcurses = true;
    initscr();
    cbreak();
    noecho();
    clear();
    scrollok(stdscr, TRUE);
}

void ConsoleHandler::closeWindow(bool prompt) {
    if (prompt) {
        print("Press any key to exit.\n");
        getch();
    }
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

std::string ConsoleHandler::getInput(size_t len, std::string prompt) {
    print(prompt);
    return getString(len);
}


std::string ConsoleHandler::getString(size_t len) {
    if (f_useNcurses) {
        char cInput[len];
        int status = getnstr(cInput, len);
        if (status != OK) {
            closeWindow(false);
            throw std::runtime_error("Something went wrong. Please restart the terminal and run bin/main again.");
        }
        std::string input(cInput);
        print(input);
        return input;
    } else {
        std::string input;
        std::cin >> input;
        return input;
    }
}