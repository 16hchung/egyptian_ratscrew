#include "abstract_view.h"

ViewBase::ViewBase(ConsoleHandler::WindowPosition position) {
    id = ConsoleHandler::newWindow(position);
}

int ViewBase::getID() {
    return id;
}

void ViewBase::clear() {
    ConsoleHandler::clearWindow(id);
}