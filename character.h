// character.h
// version 0.0.1
// classes and functions for user characters

#ifndef CHARACTER_H
#define CHARACTER_H

// CLASSES
class Character {
    public:
    protected:
};

class Party {
    public:
        void setPartyName(Screen * scr) {
            mvwscanw(scr, 5, 0, partyName);
        }
    protected:
        Character * firstChar;
        std::string partyName;

};

// FUNCTIONS
Party * newParty(Screen * scr);
Character * newCharacter(Screen * scr);

#endif
