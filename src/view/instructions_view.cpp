#include "instructions_view.h"

using Cnsl = ConsoleHandler;
using Slap = CenterCardPile::SlapType;

const std::string InstructionsView::defaultText =
    "Press SPACEBAR to put down next card. Press Q to quit.";

InstructionsView::InstructionsView() : ViewBase(ConsoleHandler::Middle) {
    printDefault();
}

void InstructionsView::printCredits(std::string winnerName) {
    Cnsl::clearWindow(getID());
    if (!winnerName.empty()) {
        Cnsl::print(winnerName + " won! Great Job!\n", getID());
    }
    Cnsl::print("A quick note: credit for playing card ASCII art goes to ejm98\n", getID());
    Cnsl::print("Link to art here: https://www.asciiart.eu/miscellaneous/playing-cards\n", getID());
    Cnsl::print("Thanks for playing! Press Q to quit.\n", getID());
    waitForSpecificKey(Cnsl::QuitGame, false);
}

void InstructionsView::printValidSlap(std::string playerName, Slap slapType) {
    // enum SlapType { Invalid, Double, Sandwich, TopBottom, Marriage, Rainbow, Affair, Divorce };
    Cnsl::clearWindow(getID());
    std::string slapString = (slapType == Slap::Double)    ? "Double"
                           : (slapType == Slap::Sandwich)  ? "Sandwich"
                           : (slapType == Slap::TopBottom) ? "Top and Bottom"
                           : (slapType == Slap::Marriage)  ? "Marriage"
                           : (slapType == Slap::Rainbow)   ? "Rainbow Affair"
                           : (slapType == Slap::Affair)    ? "Affair"
                           : (slapType == Slap::Divorce)   ? "Divorce"
                           : "Invalid";
    Cnsl::print("Valid slap by " + playerName + ": " + slapString + "\n", getID());
    Cnsl::print("Press SPACEBAR to continue.", getID());
    waitForSpecificKey(Cnsl::CardDown);
}

void InstructionsView::printInvalidSlap(std::string playerName) {
    Cnsl::clearWindow(getID());
    Cnsl::print(playerName + " made an invalid slap! Burn card added to center.\n", getID());
    Cnsl::print("Press SPACEBAR to continue.", getID());
    waitForSpecificKey(Cnsl::CardDown);
}

Cnsl::MoveType InstructionsView::printCountdownOver() {
    Cnsl::clearWindow(getID());
    Cnsl::print("Face card countdown ran out.\n", getID());
    Cnsl::print("Press SPACEBAR to continue or slap the deck if it's slappable.\n", getID());
    // if pile is slappable, want to process slap
    Cnsl::MoveType move = Cnsl::waitForMove(getID());
    while (move != Cnsl::CardDown && move != Cnsl::Player1Slap && move != Cnsl::Player2Slap) {
        move = Cnsl::waitForMove(getID());
    }
    return move;
}

void InstructionsView::printDefault() {
    Cnsl::clearWindow(getID());
    Cnsl::print(defaultText, getID());
}

void InstructionsView::waitForSpecificKey(Cnsl::MoveType moveType, bool resetContent) {
    Cnsl::MoveType move = Cnsl::waitForMove(getID());
    while (move != moveType) {
        move = Cnsl::waitForMove(getID());
    }
    if (resetContent) {
        printDefault();
    }
}
