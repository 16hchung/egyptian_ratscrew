/**
 * intro_helper.h
 * --------------
 * prints introductory tutorial on Egyptian Ratscrew gameplay
 * 
 */

#ifndef INTRO_HELPER_H
#define INTRO_HELPER_H
#include "console_handler.h"

struct IntroHelper {
public:
    // prints all instructions in order, with pauses for user to read
    static void goThroughIntro(std::string player1name, std::string player2name);

private:
    // prints section, pauses intro and prompts user to press any key before continuing
    // @param toPrint: tutorial instructions to print
    // @param isDone:  set to true if printing the last instruction
    static void printAndWait(std::string toPrint, bool isDone = false);
};

#endif