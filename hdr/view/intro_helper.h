#ifndef INTRO_HELPER_H
#define INTRO_HELPER_H
#include "console_handler.h"

struct IntroHelper {
public:
    static void goThroughIntro(std::string player1name, std::string player2name);

private:
    static void printAndWait(std::string toPrint, bool isDone = false);
};

#endif