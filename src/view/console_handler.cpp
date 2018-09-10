#include "console_handler.h"

bool ConsoleHandler::f_useNcurses = false;
std::vector<WINDOW *> ConsoleHandler::windows;
std::set<ConsoleHandler::WindowPosition> ConsoleHandler::occupiedPositions;

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

int ConsoleHandler::newWindow(ConsoleHandler::WindowPosition position) {
    if (isPositionOccupied(position)) {
        throw std::runtime_error("Trying to create window in occupied position.");
    }
    setOccupiedPosition(position, true);
    int indexID = windows.size();
    return indexID;
}

void ConsoleHandler::closeWindow(bool prompt) {
    if (prompt) {
        print("Press any key to exit.\n");
        getch();
    }
    endwin();
    f_useNcurses = false;
}

void ConsoleHandler::print(std::string str, int windowIdx) {
    if (windowIdx >= (int) windows.size()) {
        throw std::runtime_error("Invalid ID passed to ConsoleHandler::print");
    }
    WINDOW *window = (windowIdx < 0) ? stdscr : windows[windowIdx];
    if (f_useNcurses) {
        waddstr(window, str.c_str());
    } else {
        std::cout << str;
    }
}

std::string ConsoleHandler::getInput(size_t len, std::string prompt) {
    print(prompt);
    return getString(len);
}

void ConsoleHandler::coordsForPosition(ConsoleHandler::WindowPosition position, int &nlines, int &ncols, int &x, int &y) {

}

bool ConsoleHandler::isPositionOccupied(ConsoleHandler::WindowPosition position) {
    auto existingPos = occupiedPositions.find(position);
    return existingPos != occupiedPositions.end();
}

void ConsoleHandler::setOccupiedPosition(ConsoleHandler::WindowPosition position, bool isOccupied) {
    if (isOccupied) {
        occupiedPositions.insert(position);
    } else {
        occupiedPositions.erase(position);
    }
}

std::string ConsoleHandler::getString(size_t len) {
    if (f_useNcurses) {
        echo();
        char cInput[len];
        int status = getnstr(cInput, len);
        if (status != OK) {
            closeWindow(false);
            throw std::runtime_error("Something went wrong. Please restart the terminal and run bin/main again.");
        }
        std::string input(cInput);
        noecho();
        return input;
    } else {
        std::string input;
        std::cin >> input;
        return input;
    }
}