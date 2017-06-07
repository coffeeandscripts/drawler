// character.h
// version 0.0.1
// classes and functions for user characters

#ifndef CHARACTER_H
#define CHARACTER_H

// CLASSES
class Attack {
    public:
    protected:
};

class Equipment {
    public:
    protected:
};

class Character {
    public:
        void setCharName(Screen * scr) {
            //mvwscanw(scr->windows[2], 5, 0, charName);
        }
    protected:
        std::string charName;
        Character * nextChar;
};

class Party {
    public:
        void setPartyName(Screen * scr) {
            mvwscanw(scr->windows[2], 5, 0, partyName);
        }
    protected:
        Character * firstChar;
        char * partyName;

};

// FUNCTIONS
Party * newParty(Screen * scr);
Character * newCharacter(Screen * scr);
Party * partyCreation(Screen * scr);

#endif
