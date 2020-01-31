#ifndef GAME_H
#define GAME_H

#include "sfml/Window.hpp"
#include "Camera.h"

class Game {
public:
	Game();
	void mainLoop();

private:
	sf::Window window;
	sf::ContextSettings settings;
	Camera cam;

	void processInput();
};

#endif