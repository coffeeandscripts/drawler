// character.cpp
// version 0.0.1
// classes and functions for user characters

#include <ncurses.h>
#include <iostream>
#include <string>

#include "windows.h"
#include "character.h"

// CLASSES
class Party;
class Character;
class Screen;

// FUNCTIONS

void printPartyOptions(Screen * scr) {
    WINDOW * win = scr->windows[2];
    if (scr->windowDatas[2]->returnCurrentColumn() == 1 && scr->windowDatas[2]->returnCurrentRow() == 2) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, 3, 0, "New");
        wattroff(win, A_STANDOUT);
    } else {
        mvwprintw(win, 3, 0, "New");
    }
    if (scr->windowDatas[2]->returnCurrentColumn() == 2 && scr->windowDatas[2]->returnCurrentRow() == 2) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, 3, 8, "Edit");
        wattroff(win, A_STANDOUT);
    } else {
        mvwprintw(win, 3, 8, "Edit");
    }
    if (scr->windowDatas[2]->returnCurrentColumn() == 3 && scr->windowDatas[2]->returnCurrentRow() == 2) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, 3, 16, "Delete");
        wattroff(win, A_STANDOUT);
    } else {
        mvwprintw(win, 3, 16, "Delete");
    }
    if (scr->windowDatas[2]->returnCurrentColumn() == 4 && scr->windowDatas[2]->returnCurrentRow() == 2) {
        wattron(win, A_STANDOUT);
        mvwprintw(win, 3, 24, "Done");
        wattroff(win, A_STANDOUT);
    } else {
        mvwprintw(win, 3, 24, "Done");
    }
}

void printCharacters(Screen * scr, Party * currentParty) {
    int n = 0;
    WINDOW * win = scr->windows[2];
    Character * firstCharacter = currentParty->returnFirstChar();
    if (firstCharacter != NULL) {
        while (firstCharacter->returnNextChar() != NULL) {
            mvwprintw(win, 5+n, 0, firstCharacter->returnCharName());
            firstCharacter = firstCharacter->returnNextChar();
            n += 1;
        }
        mvwprintw(win, 5+n, 0, firstCharacter->returnCharName());
    }
}

void printPartyName(Screen * scr, Party * currentParty) {
    mvwprintw(scr->windows[2], 1, 0, "Party: ");
    mvwprintw(scr->windows[2], 1, 8, currentParty->returnPartyName());
    updateScreen(scr);
}

void createNewCharacter(Screen * scr, Party * newParty) {
    Character * newCharacter = new Character;
    newCharacter->setNullNext();
    newCharacter->setCharName(scr);
    newParty->addNewCharacter(newCharacter);
}

int lastKeyCharacters(Screen * scr, int ch, Party * newParty) {
    int done = 0;
    if (ch == 260) {
        scr->windowDatas[2]->decrementColumn();
    } else if (ch == 261) {
        scr->windowDatas[2]->incrementColumn();
    } else if (ch == 10 && scr->windowDatas[2]->returnCurrentColumn() == 4) {  // exit character design
        done = 1;
        scr->userScreen = 1;
    } else if (ch == 10 && scr->windowDatas[2]->returnCurrentColumn() == 1) {  // new character
        createNewCharacter(scr, newParty);
    }
    return done;
}

void partyCreation(Screen * scr, Party * newParty) {
    // Party name
    newParty->setCharNull();
    newParty->setPartyName(scr);
    // Character generation
    // display options and select: new, edit, delete, done
    int done = 0;
    int ch;
    while (done != 1) {
        printPartyOptions(scr);
        printPartyName(scr, newParty);
        printCharacters(scr, newParty);
        updateScreen(scr);
        ch = getch();
        //scr->windowDatas[2]->resetColumn();
        done = lastKeyCharacters(scr, ch, newParty);
    }
    
}
