// drawler
// engine.h
// desc: holds the function definitions and model variables

#ifndef ENGINE_H
#define ENGINE_H

#include <ncurses.h>
#include <iostream>

#include "screen.h"

class Engine {
	public:
		void start_engine();
		void end_engine();
		void run_game();
		int get_y_dim();
		int get_x_dim();
		void set_scrs(Screens *);
	protected:
		void set_dimensions();
		void get_key();
		int scr_y;
		int scr_x;
		int key;
		Screens * scrs;
};

#endif
