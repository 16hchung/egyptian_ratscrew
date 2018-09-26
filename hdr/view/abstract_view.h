/**
 * abstract_view.h
 * ---------------
 * base class for view classes, which handle UI
 */

#ifndef ABSTRACT_VIEW_H
#define ABSTRACT_VIEW_H
#include "console_handler.h"

class ViewBase {
public:
    ViewBase(ConsoleHandler::WindowPosition position, std::string label = "");

    /**
     * getter for view's id, which should remain constant once initialized
     * @return id
     */
    int getID();

    /**
     * clears contents of view
     */
    void clear();

private:
    // want to abstract out everything having to do with curses: ConsoleHandler holds pointers
    // to all panels and just gives view obj an index which serves as an id
    int id;

};

#endif