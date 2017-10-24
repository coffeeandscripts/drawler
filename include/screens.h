// drawler
// screens.h
// desc: group of screens held as linked list, individual screens, printing of generic text and movement

#ifndef SCREENS_H
#define SCREENS_H

#include <ncurses.h>
#include <iostream>

#define STR_LENGTH 64

class VarBuffer;

class Screen {
	public:
	Screen();
	void set_screen(WINDOW * win, int scr_type, int xMax, int yMax, int * rep, VarBuffer * v, int * k);
	void set_next_screen(Screen * scr);
	void draw_border();
	void print_text(char text[], int x, int y, int style);
	void print_screen();
	void refresh_screen();
	WINDOW * return_screen();
	Screen * next();
	void down();
	void up();
	void right();
	void left();
	void move_cursor(int x, int y);
	void press_enter();
	int return_type();
	protected:
	WINDOW * screen;
	int * rep_switch;
	VarBuffer * var_buffer;
	int * last_key;
	int type;
	int x;
	int y;
	int cX;
	int cY;
	int cXmax;
	int cYmax;
	Screen * next_screen;
};

class Screens {
	public:
	Screens();
	void set_var_points(int * n, VarBuffer * v, int * k);
	void remove_screen(int type);
	void make_splash_screen();
	void make_main_screen();
	void make_party_edit_create_screen();
	void attach_party_name_screen();
	int return_current_screen();
	void set_current_screen(int n);
	Screen * return_screens();
	void clear_screens();
	void move_cursor(int x, int y);
	void press_enter();
	protected:
	int * rep_switch;
	VarBuffer * var_buffer;
	int * last_key;
	Screen screens;
	Screen saved_screens;
	int current_screen;
};

#endif
