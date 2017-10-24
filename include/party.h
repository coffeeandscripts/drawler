// party.h
// desc: classes to describe party and usable characters

#ifndef SCREENS_H
#define SCREENS_H

#include <ncurses.h>
#include <iostream>

#define STR_LENGTH 64

class Character {
	public:
	private:
};

class Party {
	public:
		void set_party_name(char * name) {
			party_name = name;
		}
	private:
		char party_name[STR_LENGTH];
		char description[STR_LENGTH];
};

#endif
