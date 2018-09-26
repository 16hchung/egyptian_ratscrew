/*
Egyptian Ratscrew

Author: Heejung Chung
Description: a console-based two-player card game
 */

#ifndef MAIN_H
#define MAIN_H

int main(int argc, char const *argv[]);

/**
 * Card game behaves unexpectedly when window is resized, so this function warns the reader of that
 */
void resizeWarning();

#endif