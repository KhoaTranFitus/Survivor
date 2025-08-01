#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Assets
{
public:
	static sf::Texture PLAYER_TEXTURE;

	static sf::Texture PLAYER_RUN;

	static sf::Texture PLAYER_FIRE;

	static sf::Texture ENEMY_RUN;

	static void init();
};