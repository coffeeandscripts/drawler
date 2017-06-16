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
    static WindowData winData;
    winData.setValues(0,0,0,0);
    scr->windowDatas[0] = &winData;
    return win;
}

// opens the setup window
WINDOW * openSetupWindow(Screen * scr) {
    clear();
    WINDOW * win = newwin(scr->height, scr->width, 0, 0);
    static WindowData winData;
    winData.setValues(2,4,2,1);
    scr->windowDatas[2] = &winData;
    return win;
}

// opens the main start window
WINDOW * openMainWindow(Screen * scr) {
    clear();
    WINDOW * win = newwin(scr->height, scr->width, 0, 0);
    static WindowData winData;
    winData.setValues(3,0,1,0);
    scr->windowDatas[1] = &winData;
    return win;
}

// opens the game window
WINDOW * openGameWindow(Screen * scr) {
    clear();
    WINDOW * win = newwin(scr->height, scr->width, 0, 0);
    static WindowData winData;
    winData.setValues(6,2,1,1);
    scr->windowDatas[1] = &winData;
    return win;
}

// opens game 


// draws everything on main start window
void drawMainWindow(Screen * scr) {   
    WINDOW * win = scr->windows[1];
    if (scr->windowDatas[1]->returnCurrentRow() == 1) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, 0, 0, "Start New Game");
        wattroff(win, A_STANDOUT);
    } else {
        mvwprintw(win, 0, 0, "Start New Game");
    }
    if (scr->windowDatas[1]->returnCurrentRow() == 2) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, 1, 0, "Load");
        wattroff(win, A_STANDOUT);
    } else {
        mvwprintw(win, 1, 0, "Load");
    }
    if (scr->windowDatas[1]->returnCurrentRow() == 3) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, 2, 0, "Quit");
        wattroff(win, A_STANDOUT);
    } else {
        mvwprintw(win, 2, 0, "Quit");
    }
}

void drawSetupWindow(Screen * scr) {
    WINDOW * win = scr->windows[2];
    int currentRow = scr->windowDatas[2]->returnCurrentRow();
    int currentColumn = scr->windowDatas[2]->returnCurrentColumn();
    if (currentColumn == 1) {
        if (currentRow == 1) {

        } else {

        }
        if (currentRow == 2) {

        } else {

        }
        if (currentRow == 3) {

        } else {

        }
        if (currentRow == 4) {

        } else {

        }
    } else if (currentColumn == 2) {

    }
}

// updates the screen based on current screen
void updateScreen(Screen * scr) {
    clear();
    refresh();
    switch(scr->userScreen) {
        case 0:
            wrefresh(scr->windows[0]);
            redrawwin(scr->windows[0]);
            break;
        case 1:
            drawMainWindow(scr);
            wrefresh(scr->windows[1]);
            redrawwin(scr->windows[1]);
            break;
        case 2:
            wrefresh(scr->windows[2]);
            redrawwin(scr->windows[2]);
            break;
        case 3:
            wrefresh(scr->windows[3]);
            redrawwin(scr->windows[3]);
            break;
    }
}
