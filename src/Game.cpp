#include "glad/glad.h"

#include "Game.h"
#include "Shader.h"

#include <iostream>

Game::Game()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	window.create(sf::VideoMode(800, 600), "Terrain Demo", sf::Style::Default, settings);

	window.setActive();

	if (!gladLoadGL())
	{
		std::cout << "Error using the glad loader. Exiting." << std::endl;
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);
}

void Game::mainLoop()
{
	std::string vertSrc = Shader::loadSource("../shaders/vert.vert");
	std::string fragSrc = Shader::loadSource("../shaders/frag.frag");
	Shader cube(vertSrc, fragSrc);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
		}

		glClearColor(0.125f, 0.208f, 0.310f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.display();
	}
}