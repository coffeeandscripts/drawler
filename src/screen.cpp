// drawler
// screen.cpp
// desc: generates group of screens and functions to create and manipulate them

#include <ncurses.h>
#include <iostream>
#include <string.h>

#include "screen.h"

#define TRUE 1
#define FALSE 0

Screen * Screens::make_splash() {
	static Screen splash_scr;
	splash_scr.set_data(1, "splash");
	return &splash_scr;
}

void Screens::set_first_scr(Screen * tmp_scr) {
	scr = tmp_scr;
	scr->set_next_scr(nullptr);
}

void Screens::set_next_scr(Screen * tmp_scr) {
	Screen * s;
	while (s->get_next_scr() != nullptr) {
		s = s->get_next_scr();
	}
}

void Screens::set_vis_scr(Screen * n) {
	vis_scr = n;
}

Screen * Screens::get_first_scr() {
	return scr;
}

Screens * Screens::create_screens() {
	static Screens scrs;
	scrs.set_first_scr(scrs.make_splash());
	scrs.set_vis_scr(scrs.get_first_scr());
	return &scrs;
}

void Screens::print_scr() {
	vis_scr->print_scr();
}

void Screen::print_scr() {
	
}

Screen * Screen::get_next_scr() {
	return next_scr;
}

void Screen::set_next_scr(Screen * s) {
	next_scr = s;
}

void Screen::set_data(int val, std::string info) {
	scr_val = val;
	name = info;
}

void Screen::show_scr() {

}

void Screen::hide_scr() {

}

void Win::make_win() {

}

void Win::show_win() {

}

void Win::hide_win() {

}
