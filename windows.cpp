// windows.cpp
// version 0.0.1
// classes and functions for window creation and management

#include <ncurses.h>
#include <iostream>
#include "windows.h"

// CLASSES
class Screen;

// FUNCTIONS
// gets the screen size
void getScreenSize(Screen * scr) {
    getmaxyx(stdscr, scr->height, scr->width);
}

// opens the splash window
WINDOW * openSplashWindow(Screen * scr) {
    clear();
    WINDOW * win = newwin(scr->height, scr->width, 0, 0);
    wprintw(win, "Drawler");
    mvwprintw(win, 1, 0, "Press any button");
    return win;
}

// opens the main start window
WINDOW * openMainWindow(Screen * scr) {
    clear();
    WINDOW * win = newwin(scr->height, scr->width, 0, 0);
    scr->mainWindowData->setValues(3,0,1,0);
    return win;
}

// opens the game window
WINDOW * openGameWindow(Screen * scr) {
    clear();
    WINDOW * win = newwin(scr->height, scr->width, 0, 0);
    wprintw(win, "Game window");
    return win;
}

// opens game 


// draws everythong on main start window
void drawMainWindow(Screen * scr) {   
    if (scr->mainWindowData->returnCurrentRow() == 1) {
        wattron(scr->mainWindow, A_STANDOUT);
        mvwprintw(scr->mainWindow, 0, 0, "Start");
        wattroff(scr->mainWindow, A_STANDOUT);
    } else {
        mvwprintw(scr->mainWindow, 0, 0, "Start");
    }
    if (scr->mainWindowData->returnCurrentRow() == 2) {
        wattron(scr->mainWindow, A_STANDOUT);
        mvwprintw(scr->mainWindow, 1, 0, "Load");
        wattroff(scr->mainWindow, A_STANDOUT);
    } else {
        mvwprintw(scr->mainWindow, 1, 0, "Load");
    }
    if (scr->mainWindowData->returnCurrentRow() == 3) {
        wattron(scr->mainWindow, A_STANDOUT);
        mvwprintw(scr->mainWindow, 2, 0, "Quit");
        wattroff(scr->mainWindow, A_STANDOUT);
    } else {
        mvwprintw(scr->mainWindow, 2, 0, "Quit");
    }
}

// updates the screen based on current screen
void updateScreen(Screen * scr) {
    clear();
    refresh();
    switch(scr->userScreen) {
        case 0:
            wrefresh(scr->splashWindow);
            redrawwin(scr->splashWindow);
            break;
        case 1:
            drawMainWindow(scr);
            wrefresh(scr->mainWindow);
            redrawwin(scr->mainWindow);
            break;
        case 2:
            wrefresh(scr->gameWindow);
            redrawwin(scr->gameWindow);
            break;
    }
}
