// drawler.cpp
// version 0.01
// Main function

// PREPROCESSOR

#include <ncurses.h>
#include <iostream>

#include "windows.h"
#include "userInput.h"

// CLASSES

// FUNCTIONS

// initialises the screen
void startCurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

// MAIN

int main() {
    int ch;
    Screen scr;
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
        lastKeyUpdate(&scr, ch);
        if (scr.userScreen == 0) {
            scr.userScreen = 1;
        }
        updateScreen(&scr);
    }
    endwin();
    
    std::cout << scr.height << std::endl;
    std::cout << scr.windowDatas[0]->returnCurrentRow() << std::endl;
    std::cout << scr.lastKey << std::endl;

    return 0;
}
