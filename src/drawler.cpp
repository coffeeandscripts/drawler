// drawler
// drawler.cpp
// desc: starts game engine

#include <ncurses.h>
#include <iostream>

#include "engine.h"

int main() {
	Engine game_engine;
	game_engine.start_engine();
	game_engine.run_game();
	return 0;
}
