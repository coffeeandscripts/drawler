// game.cpp
// version 0.0.1
// classes and functions for level design and game itself

#include <ncurses.h>
#include <iostream>
#include <dirent.h>
#include <fstream>

#include "windows.h"
#include "character.h"
#include "game.h"

// FUNCTIONS

int cmpstr(char * str1, char * str2) {
    int same = 1;
    int end = 0;
    int n = 0;
    while (same == 1 && end == 0) {
        if (str1[n] == str2[n]) {
            n += 1;
        } else {
            same = 0;
        }
        if (str1[n] == '\0' && str2[n] == '\0') {
            end = 1;
        }
    }
    return same;
}

// last key press functions
int getGameKey(int ch) {
    int exit = 0;
    switch(ch) {
        case 'm':
            break;
        case 'q':
            exit = 1;
            break;
    }
    return exit;
}

void printGameOptions(Screen * scr) {
    
}

Level * lvlSelect(Screen * scr) {
    Level * lvl = new Level;
    lvl->loadLevel(scr);
    return lvl;
}

void printLevel(Screen * scr, Level * lvl) {
    WINDOW * win = scr->windows[3];
    mvwprintw(win, 0, 0, lvl->returnLvlName());
}

// MAIN game running function
void runGameLevel(Screen * scr, Party * pty) {
    int exit = 0;
    int ch;
    Level * lvl;
    lvl = lvlSelect(scr);
    while (exit != 1) {
        printGameOptions(scr);
        printLevel(scr, lvl);
        updateScreen(scr);
        ch = getch();
        exit = getGameKey(ch);
    }
}
