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
	static sf::Texture SHOOT_ENEMY;
	static sf::Texture TANKER_RUN;

	static sf::Texture GEM_TYPE1;
	static sf::Texture GEM_TYPE2;
	static sf::Texture GEM_TYPE3;

	static sf::Texture HEALTH_TYPE1;
	static sf::Texture HEALTH_TYPE2;

	static sf::Texture SHIELD;
	static sf::Texture SPEED;

	static sf::Texture ENEMY_BULLET;
	static void init();
};