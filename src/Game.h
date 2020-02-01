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

	float timeDelta = 0.0f;

	void processEvents();
	void processKeyboard();
	void processMouse();
};

#endif