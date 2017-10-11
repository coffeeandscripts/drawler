// drawler
// screens.h
// desc: group of screens held as linked list, individual screens, printing of generic text and movement

#ifndef SCREENS_H
#define SCREENS_H

#include <ncurses.h>
#include <iostream>

extern int kill_switch;

class Screen {
	public:
		void set_next(Screen * p) {
			next_screen = p;
		}
		void set_screen(WINDOW * win, int scr_type, int xMax, int yMax, int * rep) {
			screen = win;
			getmaxyx(win, y, x);
			type = scr_type;
			cXmax = xMax;
			cYmax = yMax;
			rep_switch = rep;
			cX = 0;
			cY = 0;
			next_screen = NULL;
		}
		void draw_border() {
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
		void print_text(char text[], int x, int y, int style) {
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
		void print_screen() {
			switch(type) {
				case 1:
					draw_border();
					mvwprintw(screen, 1, 1, "DRAWLER");
					mvwprintw(screen, 2, 1, "Press any key...");
					break;
				case 2:
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
			}
		}
		void refresh_screen() {
			wrefresh(screen);
			redrawwin(screen);
		}
		WINDOW * return_screen() {
			return screen;
		}
		Screen * next() {
			return next_screen;
		}
		void down() {
			if (cY < cYmax) {
				cY++;
			}
		}
		void up() {
			if (cY > 0) {
				cY--;
			}
		}
		void right() {
			if (cX < cXmax) {
				cX++;
			}
		}
		void left() {
			if (cX > 0) {
				cX--;
			}
		}
		void move_cursor(int x, int y) {
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
		void press_enter() {
			switch(type) {
				case 2:
					switch(cY) {
						case 0:
							break;
						case 1:
							break;
						case 2:
							break;
						case 3:
							break;
						case 4:
							*rep_switch = 1;
							break;
					}
					break;
			}
		}
	protected:
		WINDOW * screen;
		int * rep_switch;
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
		void set_rep_switch(int * n) {
			rep_switch = n;
		}
		void make_splash_screen() {
			WINDOW * splash_scr = newwin(10, 24, 0, 0);
			screens.set_screen(splash_scr, 1, 0, 0, rep_switch);
			set_current_screen(1);
		}
		void make_main_screen() {
			WINDOW * main_scr = newwin(24, 24, 0, 0);
			screens.set_screen(main_scr, 2, 0, 4, rep_switch);
			set_current_screen(2);
		}
		int return_current_screen() {
			return current_screen;
		}
		void set_current_screen(int n) {
			current_screen = n;
		}
		Screen * return_screens() {
			return &screens;
		}
		void clear_screens() {
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
		void move_cursor(int x, int y) {
			// must get correct screen here
			Screen * scr = &screens;
			scr->move_cursor(x, y);
		}
		void press_enter() {
			// must get correct screen here
			Screen * scr = &screens;
			scr->press_enter();
		}
	protected:
		int * rep_switch;
		Screen screens;
		int current_screen;
};

#endif
