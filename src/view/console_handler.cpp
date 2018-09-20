#include "console_handler.h"

// Declare static members
int                                      ConsoleHandler::totalNLines  = -1;
int                                      ConsoleHandler::totalNCols   = -1;
bool                                     ConsoleHandler::f_useNcurses = false;
std::vector<WINDOW *>                    ConsoleHandler::windows;
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
    // figure out coordinates
    int nlines, ncols, x, y;
    coordsForPosition(position, nlines, ncols, x, y);

    // create window
    WINDOW *window = newwin(nlines, ncols, y, x);
    // set position-specific parameters
    switch (position) {
    case MainLeft:
    case MainRight:
        scrollok(window, TRUE);
        break;
    case Bottom:
    case SmallLeft:
    case SmallRight:
        scrollok(window, FALSE);
        break;
    default:
        throw std::runtime_error("Unexpected window position passed to ConsoleHandler::newWindow");
    }
    box(window, 0, 0); // add border
    wrefresh(window);
    wgetch(window);

    // add to vector we're using to keep track of windows
    windows.push_back(window);
    return indexID;
}

void ConsoleHandler::closeWindow(bool prompt) {
    if (prompt) {
        print("Press any key to exit.\n");
        getch();
    }
    const int numWindows = windows.size();
    for (int winIdx = numWindows - 1; winIdx >= 0; winIdx--) {
        delwin(windows[winIdx]);
    }
    windows.clear();
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

int ConsoleHandler::getTotalNLines() {
    if (!f_useNcurses) {
        throw std::runtime_error("Trying to get nlines when ncurses is disabled");
    }
    if (totalNLines < 0) {
        getmaxyx(stdscr, totalNLines, totalNCols);
    }
    return totalNLines;
}

int ConsoleHandler::getTotalNCols() {
    if (!f_useNcurses) {
        throw std::runtime_error("Trying to get nlines when ncurses is disabled");
    }
    if (totalNCols < 0) {
        getmaxyx(stdscr, totalNLines, totalNCols);
    }
    return totalNCols;
}

void ConsoleHandler::coordsForPosition(ConsoleHandler::WindowPosition position, int &nlines, int &ncols, int &x, int &y) {
    const double mainLeftToTotalVerticalRatio = 2.0 / 3.0;
    const double mainLeftToTotalHorizRatio = 2.0 / 3.0;
    const double smallLeftToTotalHorizRatio = 1.0 / 2.0;
    const int bottomHeight = 3;
    nlines = getTotalNLines();
    ncols = getTotalNCols();
    switch (position) {
    case MainLeft:
        x = y = 0;
        nlines = mainLeftToTotalVerticalRatio * (double) nlines;
        ncols  = mainLeftToTotalHorizRatio    * (double) ncols;
        break;
    case MainRight:
    {
        const double horizRatio = 1.0 - mainLeftToTotalHorizRatio;
        y      = 0;
        x      = std::ceil(mainLeftToTotalHorizRatio * (double) ncols);
        nlines = mainLeftToTotalVerticalRatio        * (double) nlines;
        ncols  = horizRatio                          * (double) ncols;
        break;
    }
    case Bottom:
        x = 0;
        y = nlines - bottomHeight;
        nlines = bottomHeight;
        break;
    case SmallLeft:
    case SmallRight:
    {
        const double vertRatio = 1.0 - mainLeftToTotalVerticalRatio;
        x      = (position == SmallLeft)
               ? 0
               : std::ceil(smallLeftToTotalHorizRatio   * (double) ncols);
        y      = std::ceil(mainLeftToTotalVerticalRatio * (double) nlines);
        ncols  = smallLeftToTotalHorizRatio             * (double) ncols;
        nlines = vertRatio                              * (double) nlines - bottomHeight;
        break;
    }
    default:
        throw std::runtime_error("Unexpected window position passed to ConsoleHandler::coordsForPosition");
        break;
    }
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