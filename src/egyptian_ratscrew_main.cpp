#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include <panel.h>
#include "egyptian_ratscrew_main.h"

int main(int argc, char const *argv[])
{


    initWindow();
    char c = getch();
    closeWindow();
    std::cout << "done" << std::endl;
    return 0;
}

void initWindow() {
    initscr();
    cbreak();
    noecho();
}

void closeWindow() {
    endwin();
}

void playGame() {

}