#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.h"
#include "GameManager.h"

class Game
{
private:
	sf::RenderWindow* window;

	void updateMousePosition();
public:
	Game();
	virtual ~Game();

	void run();
	sf::RenderWindow& getWindow() { return *window; };

	void update(float deltaTime);
	void render(sf::RenderWindow& window);
};

