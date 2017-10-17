// drawler
// engine.h
// desc: engine class, main run_game loop, and response to key presses

#ifndef ENGINE_H
#define ENGINE_H

#include <ncurses.h>
#include <iostream>
#include <string.h>

#include "screens.h"

#define TRUE 1
#define FALSE 0

#define STR_LENGTH 64
#define ALT_BACKSPACE 127

class Engine {
	public:
		void make_screen() {
			initscr();
			setlocale(LC_CTYPE, "");
			raw();
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
			scrs.set_var_points(&rep_switch, &var_buffer, &last_key);
			scrs.make_splash_screen();
			refresh();
			while (last_key != 'q' && rep_switch != 1) {
				switch(rep_switch) {
					case 8: 	// show party edit create
						clear();
						refresh();
						scrs.make_party_edit_create_screen();
						break;
					case -9: 	// remove party add screen
						scrs.remove_screen(9);
						clear();
						refresh();
						break;
				}
				rep_switch = 0;
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
		VarBuffer var_buffer;
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
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					switch(last_key) {
						case KEY_RIGHT:
							scrs.move_cursor(1, 0);
							break;
						case KEY_LEFT:
							scrs.move_cursor(-1, 0);
							break;
						case 'n':
							scrs.attach_party_name_screen();
							break;
					}
					break;
				case 9:
					switch(last_key) {
						case KEY_RIGHT:
							scrs.move_cursor(1, 0);
							break;
						case KEY_LEFT:
							scrs.move_cursor(-1, 0);
							break;
						case 10:
							scrs.press_enter();
							break;
						case ALT_BACKSPACE:
							{
								int buf_len = strlen(var_buffer.char_buffer);
								var_buffer.char_buffer[buf_len-1] = '\0';
								var_buffer.char_buffer[buf_len] = (char)NULL;
							}
							break;
						default:
							{
								int buf_len = strlen(var_buffer.char_buffer);
								var_buffer.char_buffer[buf_len] = (char)last_key;
								var_buffer.char_buffer[buf_len + 1] = '\0';
							}
							break;
					}
					break;
			}
		}
};

#endif
