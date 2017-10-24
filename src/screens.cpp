// drawler
// screens.cpp
// desc: screen functions

#include <ncurses.h>
#include <iostream>

#include "screens.h"
#include "engine.h"
#include "party.h"

#define STR_LENGTH 64

Screen::Screen() {}

void Screen::set_screen(WINDOW * win, int scr_type, int xMax, int yMax, int * rep, VarBuffer * v, int * k) {
	screen = win;
	getmaxyx(win, y, x);
	type = scr_type;
	cXmax = xMax;
	cYmax = yMax;
	rep_switch = rep;
	var_buffer = v;
	last_key = k;
	cX = 0;
	cY = 0;
	next_screen = NULL;
}

void Screen::set_next_screen(Screen * scr) {
	next_screen = scr;
}

void Screen::draw_border() {
	// corners
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y-1, 0, "+");
	mvwprintw(screen, 0, x-1, "+");
	mvwprintw(screen, y-1, x-1, "+");
	int i;
	for (i = 1; i < y - 1; i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x-1, "|");
	}
	for (i = 1; i < x - 1; i++) {
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y-1, i, "-");
	}
}
void Screen::print_text(char text[], int x, int y, int style) {
	switch(style) {
		case 0:
			mvwprintw(screen, y, x, text);
			break;
		case 1:
			wattron(screen, A_STANDOUT);
			mvwprintw(screen, y, x, text);
			wattroff(screen, A_STANDOUT);
			break;
	}
}
void Screen::print_screen() {
	switch(type) {
		case 1: 	// splash screen
			draw_border();
			mvwprintw(screen, 1, 1, "DRAWLER");
			mvwprintw(screen, 2, 1, "Press any key...");
			break;
		case 2: 	// main menu
			draw_border();
			mvwprintw(screen, 1, 1, "MAIN MENU");
			switch(cY) {
				case 0:
					print_text((char *)"Play", 1, 2, 1);
					print_text((char *)"Party", 1, 3, 0);
					print_text((char *)"Editor", 1, 4, 0);
					print_text((char *)"Settings", 1, 5, 0);
					print_text((char *)"Quit", 1, 6, 0);
					break;
				case 1:
					print_text((char *)"Play", 1, 2, 0);
					print_text((char *)"Party", 1, 3, 1);
					print_text((char *)"Editor", 1, 4, 0);
					print_text((char *)"Settings", 1, 5, 0);
					print_text((char *)"Quit", 1, 6, 0);
					break;
				case 2:
					print_text((char *)"Play", 1, 2, 0);
					print_text((char *)"Party", 1, 3, 0);
					print_text((char *)"Editor", 1, 4, 1);
					print_text((char *)"Settings", 1, 5, 0);
					print_text((char *)"Quit", 1, 6, 0);
					break;
				case 3:
					print_text((char *)"Play", 1, 2, 0);
					print_text((char *)"Party", 1, 3, 0);
					print_text((char *)"Editor", 1, 4, 0);
					print_text((char *)"Settings", 1, 5, 1);
					print_text((char *)"Quit", 1, 6, 0);
					break;
				case 4:
					print_text((char *)"Play", 1, 2, 0);
					print_text((char *)"Party", 1, 3, 0);
					print_text((char *)"Editor", 1, 4, 0);
					print_text((char *)"Settings", 1, 5, 0);
					print_text((char *)"Quit", 1, 6, 1);
					break;
			}
			break;
		case 3: 	// party load
			break;
		case 4: 	// campaign load
			break;
		case 5: 	// level screen
			break;
		case 6: 	// character screen
			break;
		case 7: 	// story screen
			break;
		case 8: 	// party creation/edit
			{
				draw_border();
				int l_width = 6;
				int b_height = 3;
				if (cX == 0) {
					print_text((char *)"PARTY", 1, 1, 1);
				} else {
					print_text((char *)"Party", 1, 1, 0);
				}
				mvwprintw(screen, 0, l_width, "+");
				for (int n = 1; n < y - 1; n++) {
					mvwprintw(screen, n, l_width, "|");
				}
				mvwprintw(screen, y - 1, l_width, "+");
				mvwprintw(screen, y - b_height, l_width, "+");
				for (int n = l_width + 1; n < x; n++) {
					mvwprintw(screen, y - b_height, n, "-");
				}
				mvwprintw(screen, y - b_height, x - 1, "+");
				print_text((char *)"n - new | ", 8, y-2, 0);
				print_text((char *)"l - load | ", 18, y-2, 0);
				print_text((char *)"e - edit", 29, y-2, 0);
			}
			break;
		case 9: 	// party name window
			wclear(screen);
			draw_border();
			if (cX ==0) {
				print_text((char *)"ADD", 2, y-2, 1);
				print_text((char *)"EXIT", 8, y-2, 0);
			} else {
				print_text((char *)"ADD", 2, y-2, 0);
				print_text((char *)"EXIT", 8, y-2, 1);
			}
			print_text((char *)var_buffer->char_buffer, 2, 2, 0);
			break;
	}
}
void Screen::refresh_screen() {
	redrawwin(screen);
	wrefresh(screen);
}
WINDOW * Screen::return_screen() {
	return screen;
}
Screen * Screen::next() {
	return next_screen;
}
void Screen::down() {
	if (cY < cYmax) {
		cY++;
	}
}
void Screen::up() {
	if (cY > 0) {
		cY--;
	}
}
void Screen::right() {
	if (cX < cXmax) {
		cX++;
	}
}
void Screen::left() {
	if (cX > 0) {
		cX--;
	}
}
void Screen::move_cursor(int x, int y) {
	switch(x) {
		case 1:
			right();
			break;
		case -1:
			left();
			break;
	}
	switch(y) {
		case 1:
			down();
			break;
		case -1:
			up();
			break;
	}
}
void Screen::press_enter() {
	switch(type) {
		case 2:
			switch(cY) {
				case 0: 	// Play
					break;
				case 1: 	// Party
					*rep_switch = 8;
					break;
				case 2: 	// Editor
					break;
				case 3: 	// Settings
					break;
				case 4: 	// Quit
					*rep_switch = 1;
					break;
			}
			break;
		case 9:
			switch(cX) {
				case 0:
					break;
				case 1:
					*rep_switch = -9;
					break;
			}
	}
}

int Screen::return_type() {
	return type;
}

Screens::Screens() {}

void Screens::set_var_points(int * n, VarBuffer * v, int * k) {
	rep_switch = n;
	var_buffer = v;
	last_key = k;
}
void Screens::remove_screen(int type) {
	Screen * scr = &screens;
	Screen * prev_scr;
	while (scr->return_type() != type) {
		prev_scr = scr;
		scr = scr->next();
	}
	prev_scr->set_next_screen(scr->next());
	set_current_screen(prev_scr->return_type());
}
void Screens::make_splash_screen() {
	WINDOW * splash_scr = newwin(10, 24, 0, 0);
	screens.set_screen(splash_scr, 1, 0, 0, rep_switch, var_buffer, last_key);
	set_current_screen(1);
}
void Screens::make_main_screen() {
	WINDOW * main_scr = newwin(24, 24, 0, 0);
	screens.set_screen(main_scr, 2, 0, 4, rep_switch, var_buffer, last_key);
	set_current_screen(2);
}
void Screens::make_party_edit_create_screen() {
	WINDOW * party_scr = newwin(20, 50, 0, 0);
	screens.set_screen(party_scr, 8, 1, 0, rep_switch, var_buffer, last_key);
	set_current_screen(8);
}
void Screens::attach_party_name_screen() {
	var_buffer->char_buffer[0] = '\0';
	WINDOW * party_name = newwin(8, 24, 4, 8);
	static Screen scr;
	scr.set_screen(party_name, 9, 1, 0, rep_switch, var_buffer, last_key);
	Screen * scrs = &screens;
	while (scrs->next() != NULL) {
		scrs = scrs->next();
	}
	scrs->set_next_screen(&scr);
	set_current_screen(9);
}
int Screens::return_current_screen() {
	return current_screen;
}
void Screens::set_current_screen(int n) {
	current_screen = n;
}
Screen * Screens::return_screens() {
	return &screens;
}
void Screens::clear_screens() {
	Screen * scr = &screens;
	while (scr != NULL) {
		delwin(scr->return_screen());
		Screen * prev_scr = scr;
		scr = scr->next();
		// delete data now
	}
	clear();
	refresh();
}
void Screens::move_cursor(int x, int y) {
	Screen * scr = &screens;
	while (scr->return_type() != current_screen) {
		scr = scr->next();
	}
	scr->move_cursor(x, y);
}
void Screens::press_enter() {
	Screen * scr = &screens;
	while (scr->return_type() != current_screen) {
		scr = scr->next();
	}
	scr->press_enter();
}
