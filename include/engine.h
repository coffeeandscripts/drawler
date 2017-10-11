// drawler
// engine.h
// desc: engine class, main run_game loop, and response to key presses

#ifndef ENGINE_H
#define ENGINE_H

#include <ncurses.h>
#include <iostream>

#include "screens.h"

#define TRUE 1
#define FALSE 0

class Engine {
	public:
		void make_screen() {
			initscr();
			cbreak();
			noecho();
			keypad(stdscr, TRUE);
			curs_set(FALSE);
		}
		void set_dimensions() {
			getmaxyx(stdscr, scrY, scrX);
		}
		int height() {
			return scrY;
		}
		int width() {
			return scrX;
		}
		void run_game() {
			scrs.set_rep_switch(&rep_switch);
			scrs.make_splash_screen();
			refresh();
			while (last_key != 'q' && rep_switch != 1) {
				Screen * scr = scrs.return_screens();
				while (scr != NULL) {
					scr->print_screen();
					scr->refresh_screen();
					scr = scr->next();
				}
				refresh();
				last_key = getch();
				key_press();
			}
		}
	protected:
		int scrX;
		int scrY;
		int last_key;
		int rep_switch;
		Screens scrs;
		void key_press() {
			switch(scrs.return_current_screen()) {
				case 1:
					switch(last_key) {
						case 'q':
							break;
						default:
							scrs.clear_screens();
							scrs.make_main_screen();
							break;
					}
					break;
				case 2:
					switch(last_key) {
						case KEY_DOWN:
							scrs.move_cursor(0, 1);
							break;
						case KEY_UP:
							scrs.move_cursor(0, -1);
							break;
						case 10:
							scrs.press_enter();
							break;
					}
					break;
			}
		}
};

#endif
