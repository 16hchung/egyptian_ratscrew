#ifndef ABSTRACT_VIEW_H
#define ABSTRACT_VIEW_H
#include "console_handler.h"

class ViewBase {
public:
    ViewBase(ConsoleHandler::WindowPosition position);
    int getID();
    void clear();

private:
    // want to abstract out everything having to do with curses: ConsoleHandler holds pointers
    // to all panels and just gives view obj an index which serves as an id
    int id;

};

#endif