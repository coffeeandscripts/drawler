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

Party * newParty(Screen * scr) {
    Party * party;
    return party;
}

Character * newCharacter(Screen * scr) {
    Character * character;
    return character;
}

Party * partyCreation(Screen * scr) {
    Party newParty;
    newParty.setPartyName(scr);
    Party * newPartyAdd = &newParty;
    return newPartyAdd;
}
