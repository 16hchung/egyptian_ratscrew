#include "console_handler.h"


// Declare static members
int                                      ConsoleHandler::totalNLines  = -1;
int                                      ConsoleHandler::totalNCols   = -1;
bool                                     ConsoleHandler::f_useNcurses = false;
std::vector<WINDOW *>                    ConsoleHandler::borderWindows;
std::vector<WINDOW *>                    ConsoleHandler::contentWindows;
std::set<ConsoleHandler::WindowPosition> ConsoleHandler::occupiedPositions;


ConsoleHandler::MoveType ConsoleHandler::waitForMove(int windowIdx, 
                                                     std::string incorrectKeyText, 
                                                     bool acceptMisc) {
    const int maxTries = 10;
    // using stdscr brings default to front and clears screen
    WINDOW *scr = (contentWindows.empty()) ? stdscr 
                : (windowIdx >= 0)         ? contentWindows[windowIdx]
                : contentWindows.back();
    if (incorrectKeyText.empty()) {
        incorrectKeyText = "I don't recognize that key. "
                           "Press spacebar to put card down, Q to quit, or C to continue.\n";
    }
    for (int i = 0; i < maxTries; ++i) {
        char c = wgetch(scr);
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
            if (acceptMisc) { return Misc; }
            clearWindow(windowIdx);
            print(incorrectKeyText, windowIdx);
        }
    }
    print("That was 10 unrecognized key presses. Quitting game. Press any key.\n", windowIdx);
    wgetch(scr);
    return QuitGame;
}

void ConsoleHandler::initWindow() {
    if (f_useNcurses) { return; }
    f_useNcurses = true;
    initscr();
    cbreak();
    noecho();
    clear();
    scrollok(stdscr, TRUE);
}

int ConsoleHandler::newWindow(ConsoleHandler::WindowPosition position, std::string windowLabel) {
    if (isPositionOccupied(position)) {
        throw std::runtime_error("Trying to create window in occupied position.");
    }
    setOccupiedPosition(position, true);
    int indexID = contentWindows.size();
    // figure out coordinates
    int nlines, ncols, x, y;
    coordsForPosition(position, nlines, ncols, x, y);

    // create window border
    const int topBorderBuffer = (windowLabel.empty()) ? 1 : 2;
    const int bottomBorderBuffer = 1;
    const int totalVertBuffer = topBorderBuffer + bottomBorderBuffer;
    WINDOW *borderWindow = newwin(nlines, ncols, y, x);
    windowLabel = "\n   " + windowLabel;
    waddstr(borderWindow, windowLabel.c_str());
    box(borderWindow, 0, 0); // add border
    wrefresh(borderWindow);
    // smaller window stacked on top to preserve border
    WINDOW *contentWindow = newwin(nlines - totalVertBuffer, ncols - 2, y + topBorderBuffer, x + 1); 
    wrefresh(contentWindow);
    // set position-specific parameters
    switch (position) {
    case MainLeft:
    case MainRight:
        scrollok(contentWindow, TRUE);
        break;
    case Middle:
    case SmallLeft:
    case SmallRight:
        scrollok(contentWindow, FALSE);
        break;
    default:
        throw std::runtime_error("Unexpected window position passed to ConsoleHandler::newWindow");
    }

    // add to vector we're using to keep track of windows
    contentWindows.push_back(contentWindow);
    borderWindows.push_back(borderWindow);
    return indexID;
}

void ConsoleHandler::clearWindow(int windowId) {
    if (windowId < 0) {
        wclear(stdscr);
        wrefresh(stdscr);
    } else if (windowId < contentWindows.size()) {
        wclear(contentWindows[windowId]);
        wrefresh(contentWindows[windowId]);
    } else {
        throw std::runtime_error("unexpected window id");
    }
}

void ConsoleHandler::closeWindow() {
    if (!f_useNcurses) { return; }
    const int numWindows = contentWindows.size();
    for (int winIdx = numWindows - 1; winIdx >= 0; winIdx--) {
        delwin(contentWindows[winIdx]);
        delwin(borderWindows[winIdx]);
    }
    contentWindows.clear();
    endwin();
    f_useNcurses = false;
}

void ConsoleHandler::print(std::string str, int windowIdx) {
    if (windowIdx >= (int) contentWindows.size()) {
        throw std::runtime_error("Invalid ID passed to ConsoleHandler::print");
    }
    WINDOW *window = (windowIdx < 0) ? stdscr : contentWindows[windowIdx];
    if (f_useNcurses) {
        waddstr(window, str.c_str());
        wrefresh(window);
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
    // helpful ratios
    const double mainLeftToTotalVerticalRatio = 2.0 / 3.0;
    const double mainLeftToTotalHorizRatio = 2.0 / 3.0;
    const double smallLeftToTotalHorizRatio = 1.0 / 2.0;
    const int bottomHeight = 6;
    const double horizRatioForRightWindows = 1.0 - mainLeftToTotalHorizRatio;
    const double vertRatioForBottomWindows = 1.0 - mainLeftToTotalVerticalRatio;

    nlines = getTotalNLines();
    ncols = getTotalNCols();
    switch (position) {
    case MainLeft:
        x = y = 0;
        nlines = mainLeftToTotalVerticalRatio * (double) nlines;
        ncols  = mainLeftToTotalHorizRatio    * (double) ncols;
        break;
    case MainRight:
        y      = 0;
        x      = std::ceil(mainLeftToTotalHorizRatio * (double) ncols);
        nlines = mainLeftToTotalVerticalRatio        * (double) nlines;
        ncols  = horizRatioForRightWindows           * (double) ncols;
        break;
    case Middle:
    case SmallLeft:
    case SmallRight:
        x      = (position != SmallRight) ? 0
               : std::ceil(smallLeftToTotalHorizRatio   * (double) ncols);
        y      = std::ceil(mainLeftToTotalVerticalRatio * (double) nlines);
        y     += (position == Middle) ? 0
               : bottomHeight;
        ncols  = (position == Middle) ? ncols
               : smallLeftToTotalHorizRatio             * (double) ncols;
        nlines = (position == Middle) ? bottomHeight
               : vertRatioForBottomWindows              * (double) nlines - bottomHeight;
        break;
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
        getnstr(cInput, len);
        std::string input(cInput);
        noecho();
        return input;
    } else {
        std::string input;
        std::cin >> input;
        return input;
    }
}