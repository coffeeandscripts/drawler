// drawler.cpp
// version 0.01
// Main function

// PREPROCESSOR

#include <ncurses.h>
#include <iostream>

#include "windows.h"
#include "character.h"
#include "userInput.h"

// CLASSES
class Party;
class Screen;

// FUNCTIONS

// initialises the screen
void startCurses() {
    initscr();
    cbreak();
    echo();
    keypad(stdscr, TRUE);
    curs_set(0);
}

// MAIN

int main() {
    int ch;
    Screen scr;
    Party currentParty;
    scr.escapeCall = 0;

    startCurses();
    getScreenSize(&scr);

    scr.windows[0] = openSplashWindow(&scr);
    scr.windows[1] = openMainWindow(&scr);
    scr.windows[2] = openSetupWindow(&scr);
    scr.windows[3] = openGameWindow(&scr);
    scr.userScreen = 0;
    refresh();
    updateScreen(&scr);

    while (scr.escapeCall != 1 and ch != 'q') {
        ch = getch();
        lastKeyUpdate(&scr, ch, &currentParty);
        if (scr.userScreen == 0) {
            scr.userScreen = 1;
        }
        updateScreen(&scr);
    }
    endwin();
    
    std::cout << currentParty.returnFirstChar()->returnNextChar()->returnCharName() << std::endl;
    std::cout << currentParty.returnFirstChar()->returnCharName() << std::endl;
    std::cout << scr.userScreen << std::endl;
    std::cout << scr.lastKey << std::endl;

    return 0;
}
