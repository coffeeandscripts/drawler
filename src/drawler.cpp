// drawler
// drawler.cpp
// desc: starts game engine

#include <ncurses.h>
#include <iostream>

#include "engine.h"

int main() {
	Engine game_engine;
	game_engine.start_engine();
	std::cout << game_engine.get_x_dim() << '\n';
	return 0;
}
