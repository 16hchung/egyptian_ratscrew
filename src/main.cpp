#include <ncurses.h>
#include <panel.h>
#include "ers_game.h"
#include "main.h"

int main(int argc, char const *argv[])
{
    initWindow();
    char c = getch();
    EgyptianRatscrewGame game;
    closeWindow();
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