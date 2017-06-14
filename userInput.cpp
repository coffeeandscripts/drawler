// userInput.cpp
// version 0.0.1
// all user input functions and classes

#include <ncurses.h>
#include <iostream>

#include "windows.h"
#include "character.h"
#include "userInput.h"

// CLASSES
class Screen;
class Party;

// FUNCTIONS
// updates scr data using the latest keystroke
void lastKeyUpdate(Screen * scr, int ch, Party * currentParty) {
    switch(ch) {
        case '1':
            if (scr->userScreen != 1) {
                scr->userScreen = 1;
                updateScreen(scr);
            }
            break;
        case '2':
            if (scr->userScreen != 2) {
                scr->userScreen = 2;
                updateScreen(scr);
            }
            break;
        case 10: // enter
            switch (scr->userScreen) {
                case 1:
                    switch (scr->windowDatas[1]->returnCurrentRow()) {
                        case 1:  // start new game - goes into party/character creation
                            scr->userScreen = 2;
                            partyCreation(scr, currentParty);                    
                            break;
                        case 2:
                            break;
                        case 3:
                            scr->escapeCall = 1;
                            break;
                    }
                    break;
                case 2:
                    break;
            }
            break;
        case 258: // down
            switch (scr->userScreen) {
                case 1:
                    // increases the row data value for the rows on the main menu
                    scr->windowDatas[1]->incrementRow();                    
                    break;
                case 2:
                    break;
            }
            break;
        case 259: // up
            switch (scr->userScreen) {
                case 1:
                    // decreases the row data value for the rows on the main menu
                    scr->windowDatas[1]->decrementRow();
                    break;
                case 2:
                    break;
            }

            break;
        case 260: // left
            break;
        case 261: // right
            break;
    }
    scr->lastKey = ch;
}
