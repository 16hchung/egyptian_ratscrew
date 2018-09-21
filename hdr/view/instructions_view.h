#ifndef INSTRUCTIONS_VIEW_H
#define INSTRUCTIONS_VIEW_H
#include "abstract_view.h"

class InstructionsView : public ViewBase {
public:
    InstructionsView() : ViewBase(ConsoleHandler::Middle) {}

private:
    static const std::string defaultText;
};


#endif