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
            int n = 0;
            int ch;
            while (ch != 10) {
                ch = mvwgetch(scr->windows[2], 5, n);
                partyName[n] = ch;
                n += 1;
            }
        }
        char * returnPartyName() {
            return partyName;
        }
    protected:
        Character * firstChar;
        char * partyName;

};

// FUNCTIONS
Party * newParty(Screen * scr);
Character * newCharacter(Screen * scr);
void partyCreation(Screen * scr, Party * newParty);

#endif
