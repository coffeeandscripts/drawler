// drawler
// engine.h
// desc: engine class, main run_game loop, and response to key presses

#ifndef ENGINE_H
#define ENGINE_H

#include <ncurses.h>
#include <iostream>
#include <string.h>

#include "screens.h" 		// include and not forward declared since FD only allows pointers

#define TRUE 1
#define FALSE 0

#define STR_LENGTH 64
#define ALT_BACKSPACE 127

class VarBuffer {
	public:
	VarBuffer();
	int int_buffer;
	char char_buffer[STR_LENGTH];
	int type;
	void set_next(VarBuffer * v);
	private:
	VarBuffer * next;
};

class Engine {
	public:
	Engine();
	void make_screen();
	void set_dimensions();
	int height();
	int width();
	void run_game();
	void key_press();
	protected:
	int scrX;
	int scrY;
	int last_key;
	int rep_switch;
	VarBuffer var_buffer;
	Screens scrs;
};

#endif
