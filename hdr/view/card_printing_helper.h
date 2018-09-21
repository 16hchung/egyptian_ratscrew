#ifndef CARD_PRINTING_HELPER_H
#define CARD_PRINTING_HELPER_H
#include "common_hdrs.h"

struct CardPrintingHelper {
public:
    static std::string printableStringForCardID(std::string cardID);

private:
    static std::map<std::string, std::string> cardIDToPrintableString;

};


#endif