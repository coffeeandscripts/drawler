// drawler
// engine.cpp
// desc: starts ncurses screen and allows for output and input of data

#include <ncurses.h>
#include <iostream>

#include "engine.h"
#include "screen.h"

#define TRUE 1
#define FALSE 0

void Engine::start_engine() {
	initscr();
	setlocale(LC_CTYPE, "");
	raw();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	set_dimensions();
}

void Engine::end_engine() {
	endwin();
}

void Engine::set_dimensions() {
	getmaxyx(stdscr, scr_y, scr_x);
}

int Engine::get_y_dim() {
	return scr_y;
}

int Engine::get_x_dim() {
	return scr_x;
}

void Engine::get_key() {
	key = getch();
}

void Engine::set_scrs(Screens * tmp_scrs) {
	scrs = tmp_scrs;
}

void Engine::run_game() {
	scrs = create_screens();
	while (key != 'q') {
		get_key();
		refresh(); 	// move to screens class later
	}
}
