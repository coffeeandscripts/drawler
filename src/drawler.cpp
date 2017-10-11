// drawler
// drawler.cpp
// desc: main function that runs the game engine.

#include <ncurses.h>
#include <iostream>

#include "engine.h"
#include "screens.h"

int main() {
	Engine engine;
	engine.make_screen();
	engine.set_dimensions();
	engine.run_game();
	endwin();
	return 0;
}
