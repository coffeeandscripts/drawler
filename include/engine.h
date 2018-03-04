// drawler
// engine.h
// desc: holds the function definitions and model variables

#ifndef ENGINE_H
#define ENGINE_H

#include <ncurses.h>
#include <iostream>

class Engine {
	public:
		void start_engine();
		void end_engine();
		int get_y_dim();
		int get_x_dim();
	protected:
		void set_dimensions();
		int scr_y;
		int scr_x;
};

#endif
