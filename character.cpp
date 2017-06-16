// character.cpp
// version 0.0.1
// classes and functions for user characters

#include <ncurses.h>
#include <iostream>
#include <string>
#include <fstream>

#include "windows.h"
#include "character.h"
#include "game.h"

// CLASSES
class Party;
class Character;
class Screen;

// FUNCTIONS
// print the options at the top on what you can do for the party creation
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

// prints each of the character ** will add printing of stats
void printCharacters(Screen * scr, Party * currentParty) {
    int n = 0;
    WINDOW * win = scr->windows[2];
    Character * firstCharacter = currentParty->returnFirstChar();
    if (firstCharacter != NULL) {
        while (firstCharacter->returnNextChar() != NULL) {
            if (scr->windowDatas[2]->returnCurrentRow() == n+3) {
                wattron(win, A_STANDOUT);
                mvwprintw(win, 5+n, 0, firstCharacter->returnCharName());
                wattroff(win, A_STANDOUT);
            } else {
                mvwprintw(win, 5+n, 0, firstCharacter->returnCharName());
            }
            firstCharacter = firstCharacter->returnNextChar();
            n += 1;
        }
        if (scr->windowDatas[2]->returnCurrentRow() == n+3) {
            wattron(win, A_STANDOUT);
            mvwprintw(win, 5+n, 0, firstCharacter->returnCharName());
            wattroff(win, A_STANDOUT);
        } else {
            mvwprintw(win, 5+n, 0, firstCharacter->returnCharName());
        }
    }
}

// prints the name of the party at the top
void printPartyName(Screen * scr, Party * currentParty) {
    mvwprintw(scr->windows[2], 1, 0, "Party: ");
    mvwprintw(scr->windows[2], 1, 8, currentParty->returnPartyName());
    updateScreen(scr);
}

// allows for the creation of a new character
void createNewCharacter(Screen * scr, Party * newParty) {
    Character * newCharacter = new Character;
    newCharacter->setNullNext();
    newCharacter->setCharName(scr);
    newParty->addNewCharacter(newCharacter);
    scr->windowDatas[2]->addRow();
}

// key choice function specific to deletion of characters
void deleteLastKey(Screen * scr, int ch, Party * currentParty) {
    if (ch == 258) {
        scr->windowDatas[2]->incrementRow();
    } else if (ch == 259) {
        if (scr->windowDatas[2]->returnCurrentRow() > 3) {
            scr->windowDatas[2]->decrementRow();
        }
    } else if (ch == 10) {
        int deleteCounter = scr->windowDatas[2]->returnCurrentRow() - 3;    // 0 being the first one
        int n = 0;
        Character * firstCharacter = currentParty->returnFirstChar();
        Character * prevCharacter = NULL;
        while (n != deleteCounter) {
            prevCharacter = firstCharacter;
            firstCharacter = firstCharacter->returnNextChar();
            n += 1;
        }
        if (prevCharacter != NULL) {
            prevCharacter->setNext(firstCharacter->returnNextChar());
        } else {
            currentParty->setFirstChar(firstCharacter->returnNextChar());
        }
        delete firstCharacter;
        scr->windowDatas[2]->removeRow();
        if (scr->windowDatas[2]->returnCurrentRow() > 3) {
            scr->windowDatas[2]->decrementRow();
        }
        werase(scr->windows[2]);
    }
}

// allows for the deletion of characters
void deleteCharacter(Screen * scr, Party * currentParty) {
    int ch = 0;
    while (ch != 'q') {
        printPartyOptions(scr);
        printPartyName(scr, currentParty);
        printCharacters(scr, currentParty);
        updateScreen(scr);
        ch = getch();
        deleteLastKey(scr, ch, currentParty);
    }
    scr->windowDatas[2]->resetRow(2);
}

// key choice function for majority of party setup
int lastKeyCharacters(Screen * scr, int ch, Party * newParty) {
    int done = 0;
    if (ch == 260) {
        scr->windowDatas[2]->decrementColumn();
    } else if (ch == 261) {
        scr->windowDatas[2]->incrementColumn();
    } else if (ch == 'q') {  // exit character design
        done = 1;
        scr->userScreen = 1;
    } else if (ch == 10 && scr->windowDatas[2]->returnCurrentColumn() == 1) {  // new character
        createNewCharacter(scr, newParty);
    } else if (ch == 10 && scr->windowDatas[2]->returnCurrentColumn() == 3) {  // delete character
        scr->windowDatas[2]->resetRow(3);
        deleteCharacter(scr, newParty);
    } else if (ch == 10 && scr->windowDatas[2]->returnCurrentColumn() == 4) {  // start game
        if (newParty->returnFirstChar() != NULL) {
            scr->userScreen = 3;
            done = 1;
        }
    }
    return done;
}

// MAIN party creation
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
