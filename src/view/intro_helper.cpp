#include "intro_helper.h"
#include "console_handler.h"

using Cnsl = ConsoleHandler;

void IntroHelper::goThroughIntro(std::string player1name, std::string player2name) {
    std::string printNext =
    "These instructions are adapted from this page: https://en.wikipedia.org/wiki/Egyptian_Ratscrew\n\n"
    "Egyptian ratscrew is played with a standard card deck, which is delt evenly between the two players. "
    "Each player should start with a hand of 26 cards.\n\n"
    "OBJECTIVE:\n"
    "----------\n"
    "Collect all cards in the deck into your hand OR make your opponent lose all cards in their hand\n";
    printAndWait(printNext);

    printNext = 
    "GAMEPLAY:\n"
    "---------\n"
    "You each take turns placing down a card (from the top of your hand) onto a \"central pile\". "
    "For example, " + player1name + " puts down a card, then " + player2name + ","
    " then " + player1name + ", so on and so forth.\n";
    printAndWait(printNext);

    printNext = 
    "You continue alternating until a player places down a face card, which starts a \"countdown\". "
    "The next player then has several chances to put down another face card before the countdown runs out. "
    "The number of changes depends on the specific rank.\n\n"
    "The countdown starts at 4 cards an Ace, 3 for a King, 2 for a Queen, 1 for a Jack.\n";
    printAndWait(printNext);

    printNext =
    "If the player fails to place down a face card before the countdown runs out, the original player"
    "(who placed the face card) collects the central pile. This means all cards in the center are "
    "added to the bottom of their hand.\n";
    printAndWait(printNext);

    printNext =
    "*** Slapping ***\n"
    "When certain sequences of cards are placed down, the central pile can become \"slappable\". "
    "Here is a list of slappable conditions:\n\n"
    "   Double:.........2 cards of the same rank are placed down in a row\n"
    "   Sandwich:.......a card is placed down with the same rank as 2 cards ago.\n"
    "                   e.g. 5 of hearts, A of spades, 5 of diamonds\n"
    "   Top and bottom: the card placed down has the same rank as the bottom card in the central pile\n"
    "   Marriage:.......a King is placed down, followed by a Queen, or vice versa\n"
    "   Divorce:........a King and Queen are placed down with any card in between (like a sandwich)\n"
    "   Affair:.........a Queen is placed down, followed by a Jack, or vice versa\n"
    "   Rainbow Affair: a King is placed down, followed by a Jack, or vice versa\n";
    printAndWait(printNext);

    printNext =
    "If the pile is slappable, whoever slaps first collects the central pile. "
    "This applies even in the middle of a face card countdown.\n\n"
    "If the pile is not slappable, any player who slaps must \"burn\" a card, placing down an extra "
    "card at the bottom of the central pile. In this interface, the central and burn piles are displayed "
    "separately for clarity.\n";
    printAndWait(printNext);

    printNext = "Those are all the rules! You're ready to play!\n";
    printAndWait(printNext);
}

void IntroHelper::printAndWait(std::string toPrint, bool isDone) {
    Cnsl::print(toPrint);
    if (isDone) {
        Cnsl::print("Press any key to start game.\n");
        Cnsl::print("Note: once you start, you won't be able to see these instructions again.");
    } else {
        Cnsl::print("Press any key to continue.\n\n");
    }
    Cnsl::waitForMove(-1, "", true);
}