#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Assets
{
public:
	static sf::Texture PLAYER_TEXTURE;

	static sf::Texture PLAYER_RUN;

	static sf::Texture PLAYER_FIRE;
		
	static sf::Texture PLAYER_HURT;

	static sf::Texture PLAYER_DIE;

	static sf::Texture ENEMY_RUN;

	static void init();
};