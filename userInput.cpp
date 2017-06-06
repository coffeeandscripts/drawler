// userInput.cpp
// version 0.0.1
// all user input functions and classes

#include <ncurses.h>
#include <iostream>
#include "windows.h"
#include "userInput.h"

// FUNCTIONS
// updates scr data using the latest keystroke
void lastKeyUpdate(Screen * scr, int ch) {
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
                    switch (scr->mainWindowData->returnCurrentRow()) {
                        case 1:
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
                    scr->mainWindowData->incrementRow();                    
                    break;
                case 2:
                    break;
            }
            break;
        case 259: // up
            switch (scr->userScreen) {
                case 1:
                    // decreases the row data value for the rows on the main menu
                    scr->mainWindowData->decrementRow();
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
