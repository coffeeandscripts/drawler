// game.h
// version 0.0.1
// classes and functions for level design and game itself

#ifndef GAME_H
#define GAME_H

// CLASSES
class Tile {
    public:
        void setNextTile(Tile * nextTileAddr) {
            nextTile = nextTileAddr;
        }
        void setNextNull() {
            nextTile = NULL;
        }
        void setTypeTile(int n) {
            tileType = n;
        }
        Tile * returnNextTile() {
            return nextTile;
        }
        int  returnTileType() {
            return tileType;
        }
    private:
        int tileType;
        /* 0 - new line
         * 1 - wall
         * 2 - ground
         * 3 - hole
         * 4
         * 5
         * 6
         * 7
         * 8
         * 9
         */
        void * linkAddr;
        Tile * nextTile;
};

class Command {
    public:
    private:
};

int cmpstr(char * str1, char * str2);

class Level {
    public:
        void loadLevel(/*char * lvlFileName*/Screen * scr) {
            std::ifstream is("levels/lvl1");
            is >> std::noskipws;
            int setFirstTile = 0;
            int ch;
            char word[6400];
            int n = 0;
            int m;
            int endStream = 0;
            Tile * tileAddr;
            while (endStream == 0) {
                is >> word[n];
                n += 1;
                word[n] = '\0';
                if (word[n - 1] == '\n') {
                    n = 0;
                    word[n] = '\0';
                }
                if (cmpstr(word, (char *)"START") == 1) {
                    n = 0;
                    m = 0;
                    is >> word[m];
                    while (word[m] != '\n') {
                        is >> word[m];
                        if (word[m] != '\n') {
                            lvlName[m] = word[m];
                            m += 1;
                        }
                    }
                } else if (cmpstr(word, (char *)"MAP_START") == 1) {
                    is >> word[m];
                    n = 0;
                    m = 0;
                    while (cmpstr(word, (char *)"MAP_END") != 1) {
                        is >> word[m];
                        if (word[m] != '\n') {
                            // add new tile
                            Tile * newTile = new Tile;
                            newTile->setNextNull();
                            switch(word[m]) {
                                case '.':
                                    newTile->setTypeTile(1);
                                    break;
                                case ' ':
                                    newTile->setTypeTile(2);
                                    break;
                                case 'O':
                                    newTile->setTypeTile(3);
                                    break;
                                default:
                                    newTile->setTypeTile(2);
                                    break;
                            }
                            if (setFirstTile == 0) {
                                firstTile = newTile;
                                setFirstTile = 1;
                            } else {
                                tileAddr = firstTile;
                                while (tileAddr->returnNextTile() != NULL) {
                                    tileAddr = tileAddr->returnNextTile();
                                }
                                tileAddr->setNextTile(newTile);
                            }
                            m += 1;
                            word[m] = '\0';
                        } else {
                            // add new line tile
                            Tile * newTile = new Tile;
                            newTile->setNextNull();
                            newTile->setTypeTile(0);
                            tileAddr = firstTile;
                            while (tileAddr->returnNextTile() != NULL) {
                                tileAddr = tileAddr->returnNextTile();
                            }
                            tileAddr->setNextTile(newTile);
                            m = 0;
                            word[m] = '\0';
                        }
                    }
                } else if (cmpstr(word, (char *)"END") == 1) {
                    endStream = 1;
                }
            }
            is.close();
        }
        Tile * returnFirstTile() {
            return firstTile;
        }
        char * returnLvlName() {
            return lvlName;
        }
    private:
        char lvlName[64];
        Tile * firstTile;
};


// FUNCTIONS
void runGameLevel(Screen * scr, Party * pty);

#endif
