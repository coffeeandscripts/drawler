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
	strcat(dir_path, path);
	std::cout << "Loading data from " << dir_path << std::endl;
	boost::filesystem::path dir(dir_path);
	int return_val = 0;
	if (boost::filesystem::create_directory(dir)) {
		return_val = 1;
	}
	if (boost::filesystem::exists(dir)) {
		return_val = 1;
	} else {
		return_val = 0;
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
