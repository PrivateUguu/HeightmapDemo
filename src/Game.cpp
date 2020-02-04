#include "Game.h"
#include "Shader.h"
#include "Terrain.h"

#include "glad/glad.h"

#include <iostream>

const int screenWidth = 800;
const int screenHeight = 600;

const int gridWidth = 4;
const int gridHeight = 4;

const float fov = 45.0f;
const float near = 0.1f;
const float far = 200.0f;
const float aRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

sf::Vector2i wCenter(screenWidth/2, screenHeight/2);

Game::Game()
	:cam(Camera())
{
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	window.create(sf::VideoMode(screenWidth, screenHeight), "Terrain Demo", sf::Style::Default, settings);
	window.setFramerateLimit(120);
	window.setMouseCursorVisible(false);
	window.setActive();

	if (!gladLoadGL())
	{
		std::cout << "Error using the glad loader. Exiting." << std::endl;
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			break;
		case sf::Event::MouseMoved:
			processMouse();
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::processKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		cam.moveForwards(timeDelta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		cam.moveLeft(timeDelta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		cam.moveBackwards(timeDelta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		cam.moveRight(timeDelta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		cam.moveUp(timeDelta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		cam.moveDown(timeDelta);
}

void Game::processMouse()
{
	sf::Vector2i mPos(sf::Mouse::getPosition(window));
	cam.updateOrientation(mPos.x - wCenter.x, mPos.y - wCenter.y);
	if (sf::Mouse::getPosition(window) != wCenter)
		sf::Mouse::setPosition(wCenter, window);
}

void Game::mainLoop()
{
	std::string tVertSrc = Shader::loadSource("../shaders/terrainVert.vert");
	std::string tFragSrc = Shader::loadSource("../shaders/terrainFrag.frag");

	Shader tshader(tVertSrc, tFragSrc);
	tshader.use();
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	glm::mat4 projection = glm::perspective(fov, aRatio, near, far);
	glm::vec4 color(1.0f, 1.0f, 0.0f, 1.0f);

	tshader.setMat4("model", model);
	tshader.setMat4("view", view);
	tshader.setMat4("projection", projection);
	tshader.setVec4("color", color);

	Terrain terrain(50, 50);

	sf::Clock clock;
	sf::Time time;
	float currentFrameTime = 0.0f;
	float lastFrameTime = 0.0f;

	while (window.isOpen())
	{
		time = clock.getElapsedTime();
		currentFrameTime = time.asSeconds();
		timeDelta = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		processEvents();
		processKeyboard();

		glClearColor(0.125f, 0.208f, 0.310f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tshader.use();
		tshader.setMat4("view", cam.viewMatrix());
		terrain.drawTerrain();

		window.display();
	}
}