// drawler
// screen.h
// desc: holds the function definitions and model variables

#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>
#include <iostream>
#include <string.h>

// a single window
class Win {
	public:
		void make_win();
		void show_win();
		void hide_win();
	protected:
		WINDOW * win;
		int win_x;
		int win_y;
		int left;
		int top;
		Win * next_win;
};

// a group of windows
class Screen {
	public:
		void show_scr();
		void hide_scr();
		void set_data(int, std::string);
		Screen * get_next_scr();
		void set_next_scr(Screen *);
		void print_scr();
	protected:
		Win * win;
		Screen * next_scr;
		int scr_val;
		std::string name;
};

// linked list of screens
class Screens {
	public:
		Screens * create_screens();
		Screen * get_first_scr();
		void set_vis_scr(Screen *);
		void set_first_scr(Screen *);
		void set_next_scr(Screen *);
		Screen * make_splash();
		void print_scr();
	protected:
		Screen * scr;
		Screen * vis_scr;
};

#endif
