// drawler
// drawler.cpp
// desc: main function that runs the game engine.

#include <ncurses.h>
#include <iostream>
#include <boost/filesystem.hpp>

#include "engine.h"
#include "screens.h"

int env_setup() {
	const char* home_path = getenv("HOME");
	const char* path = "/.drawler";
	char dir_path[256];
	strcpy(dir_path, home_path);
	strncat(dir_path, path, sizeof(dir_path));
	boost::filesystem::path dir(dir_path);
	int return_val = 0;
	if (boost::filesystem::create_directory(dir)) {
		return_val = 1;
	}
	return return_val;
}

int main() {
	if (env_setup()) {
		Engine engine;
		engine.make_screen();
		engine.set_dimensions();
		engine.run_game();
		endwin();
	}
	return 0;
}
