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

class Stats {
    public:
    protected:
        int hitPointsMaximum;
        int currentHitPoints;
        int tempHitPoints;
        int armourClass;
        int initiative;
        int speed;
        int inspiration;
        int proficiencyBonus;
        int strength;
        int dexterity;
        int consitution;
        int intelligence;
        int wisdom;
        int charisma;
        int svStrength;
        int svDexterity;
        int svConsitution;
        int svIntelligence;
        int svWisdom;
        int svCharisma;
        int acrobatics;
        int animalHandling;
        int arcana;
        int athletics;
        int deception;
        int history;
        int insight;
        int intimidation;
        int investigation;
        int medicine;
        int nature;
        int perception;
        int performance;
        int persuasion;
        int religion;
        int sleightOfHand;
        int stealth;
        int survival;
        int passiveWisdom;
};

class Character {
    public:
        void setCharName(Screen * scr) {
            mvwprintw(scr->windows[2], 4, 24, "Character name:");
            updateScreen(scr);
            int n = 0;
            int ch;
            while (ch != 10) {
                ch = mvwgetch(scr->windows[2], 5, n+24);
                if (ch != 10) {
                    charName[n] = ch;
                }
                n += 1;
                charName[n] = '\0';
            }
            werase(scr->windows[2]);
            
        }
        char * returnCharName() {
            return charName;
        }
        void setNullNext() {
            nextChar = NULL;
        }
        void setNext(Character * newCharacter) {
            nextChar = newCharacter;
        }
        Character * returnNextChar() {
            return nextChar;
        }
    protected:
        char charName[64];
        Character * nextChar;
        char charClass[64];
        int charLvl;
        char charBackground[64];
        char charRace[64];
        char charAlignment[64];
        int exp;
};

class Party {
    public:
        void setPartyName(Screen * scr) {
            mvwprintw(scr->windows[2], 4, 0, "Party name:");
            updateScreen(scr);
            int n = 0;
            int ch;
            while (ch != 10) {
                ch = mvwgetch(scr->windows[2], 5, n);
                if (ch != 10) {
                    partyName[n] = ch;
                }
                n += 1;
                partyName[n] = '\0';
            }
            werase(scr->windows[2]);
            //partyNameLength = n;
        }
        char * returnPartyName() {
            return partyName;
        }
        void addNewCharacter(Character * newCharacter) {
            Character * firstCharacter = firstChar; 
            if (firstCharacter != NULL) {
                while (firstCharacter->returnNextChar() != NULL) {
                    firstCharacter = firstCharacter->returnNextChar();
                }
                firstCharacter->setNext(newCharacter);
            } else if (firstCharacter == NULL) {
                firstChar = newCharacter;
            }
        }
        Character * returnFirstChar() {
            return firstChar;
        }
        void setFirstChar(Character * charAddr) {
            firstChar = charAddr;
        }
        void setCharNull() {
            firstChar = NULL;
        }
    protected:
        Character * firstChar;
        char partyName[64];
        //int partyNameLength;

};

// FUNCTIONS
Party * newParty(Screen * scr);
Character * newCharacter(Screen * scr);
void partyCreation(Screen * scr, Party * newParty);
int lastKeyCharacters(Screen * scr, int ch, Party * newParty);
void printPartyName(Screen * scr, Party * currentParty);
void deleteCharacter(Screen * scr, Party * currentParty);
void deleteLastKey(Screen * scr, int ch, Party * currentParty);

#endif
