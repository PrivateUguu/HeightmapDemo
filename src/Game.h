#ifndef GAME_H
#define GAME_H

#include "sfml/Window.hpp"

class Game {
public:
	Game();
	void mainLoop();

private:
	sf::Window window;
	sf::ContextSettings settings;
};

#endif