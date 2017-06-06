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

    scr.splashWindow = openSplashWindow(&scr);
    scr.mainWindow = openMainWindow(&scr);
    scr.gameWindow = openGameWindow(&scr);
    scr.userScreen = 0;
    refresh();
    updateScreen(&scr);

    while (scr.escapeCall != 1) {
        ch = getch();
        lastKeyUpdate(&scr, ch);
        if (scr.userScreen == 0) {
            scr.userScreen = 1;
        }
        updateScreen(&scr);
    }
    endwin();
    
    std::cout << scr.height << std::endl;
    std::cout << scr.mainWindowData->returnCurrentRow() << std::endl;
    std::cout << scr.lastKey << std::endl;

    return 0;
}
