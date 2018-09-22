#include "abstract_view.h"

ViewBase::ViewBase(ConsoleHandler::WindowPosition position, std::string label) {
    id = ConsoleHandler::newWindow(position, label);
}

int ViewBase::getID() {
    return id;
}

void ViewBase::clear() {
    ConsoleHandler::clearWindow(id);
}