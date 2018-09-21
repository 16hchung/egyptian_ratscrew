#include "card.h"
#include "card_string_reps.h"

using rnk = Card::Rank;

const std::vector<rnk> Card::possibleRanks = { rnk::Ace, rnk::Two, rnk::Three, rnk::Four, rnk::Five, 
    rnk::Six, rnk::Seven, rnk::Eight, rnk::Nine, rnk::Ten, rnk::Jack, rnk::Queen, rnk::King };

// Constructor
Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank) {
}

std::string Card::toString() {
    if (stringRepresentation.empty()) {
        stringRepresentation = generateStringRepresentation();
    }
    return stringRepresentation;
    // return suitString()  + ", " + static_cast<char>(rank);
}

std::string Card::suitString() {
    switch (suit) {
    case Hearts:
        return "Hearts";
    case Spades:
        return "Spades";
    case Diamonds:
        return "Diamonds";
    case Clubs:
        return "Clubs";
    }
}

std::string Card::generateStringRepresentation() {
    std::string suitTemplate = 
        (suit == Hearts)   ? CardStringTemplates::heartsTemplate   :
        (suit == Spades)   ? CardStringTemplates::spadesTemplate   :
        (suit == Diamonds) ? CardStringTemplates::diamondsTemplate :
                             CardStringTemplates::clubsTemplate;
    // rank of 10 is only one requiring two characters
    std::string replacementWithSpace = " ";
    replacementWithSpace += static_cast<char>(rank);
    std::string placeholderReplacement = (rank == Rank::Ten) ? "10" : replacementWithSpace;
    std::regex placeholderRegex(CardStringTemplates::templatePlaceholder);
    return std::regex_replace(suitTemplate, placeholderRegex, placeholderReplacement);
}