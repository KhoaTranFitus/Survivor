#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Assets
{
public:
	static sf::Texture PLAYER_TEXTURE;

	static sf::Texture PLAYER_RUN;
	static sf::Texture PLAYER_FIRE;
	static sf::Texture PLAYER_HURT;
	static sf::Texture PLAYER_DIE;

	static sf::Texture PLAYER_ARROW;
	static sf::Texture ENEMY_RUN;
	static sf::Texture SHOOT_ENEMY;
	static sf::Texture TANKER_RUN;
	static sf::Texture DASH_RUN;
	static sf::Texture BURST_RUN;

	static sf::Texture BOSS_RUN;
	static sf::Texture BOSS_FIRE;
	static sf::Texture BOSS_DIE;

	static sf::Texture GEM_TYPE1;
	static sf::Texture GEM_TYPE2;
	static sf::Texture GEM_TYPE3;

	static sf::Texture HEALTH_TYPE1;
	static sf::Texture HEALTH_TYPE2;
	static sf::Texture SHIELD;
	static sf::Texture SPEED;

	static sf::Texture ENEMY_BULLET;
	static sf::Texture BOSS_BULLET;
	static sf::Texture BURST_BULLET;

	static sf::SoundBuffer GEM_PICKUP_S;
	static sf::Sound GEM_PICKUP_SOUND;
	static sf::SoundBuffer POWERUP_PICKUP_S;
	static sf::Sound POWERUP_PICKUP_SOUND;

	static sf::SoundBuffer PLAYER_HURT_S;
	static sf::Sound PLAYER_HURT_SOUND;


	static sf::Texture SPEED_ITEM;
	static sf::Texture SHIELD_ITEM;


	static void init();
};