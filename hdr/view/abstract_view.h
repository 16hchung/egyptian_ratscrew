#ifndef ABSTRACT_VIEW_H
#define ABSTRACT_VIEW_H
#include "console_handler.h"

class ViewBase {
public:
    ViewBase(int ID) : ID(ID) {}

    // want to abstract out everything having to do with curses: ConsoleHandler holds pointers
    // to all panels and just gives view obj an index which serves as an id
    const int ID;
protected:

};

#endif