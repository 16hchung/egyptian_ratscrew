/**
 * card_string_reps.h
 * ------------------
 * used to keep all playing card ascii art in separate file 
 */

#ifndef CARD_STR_REPS_H
#define CARD_STR_REPS_H

namespace CardStringTemplates {
    static const std::string templatePlaceholder = "XX";

    static const std::string heartsTemplate = 
        "  _________  \n"
        " |XX       | \n"
        " |   _ _   | \n"
        " |  ( v )  | \n"
        " |   \\ /   | \n"
        " |    .    | \n"
        " |         | \n"
        " |_______XX| \n";


    static const std::string clubsTemplate = 
        "  _________  \n"
        " |XX       | \n"
        " |    _    | \n"
        " |   ( )   | \n"
        " |  (_'_)  | \n"
        " |    |    | \n"
        " |         | \n"
        " |_______XX| \n";

    static const std::string spadesTemplate = 
        "  _________  \n"
        " |XX       | \n"
        " |    .    | \n"
        " |   /.\\   | \n"
        " |  (_._)  | \n"
        " |    |    | \n"
        " |         | \n"
        " |_______XX| \n";
           

    static const std::string diamondsTemplate = 
        "  _________  \n"
        " |XX       | \n"
        " |    ^    | \n"
        " |   / \\   | \n"
        " |   \\ /   | \n"
        " |    v    | \n"
        " |         | \n"
        " |_______XX| \n";
    
}

#endif