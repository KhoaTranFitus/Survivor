#include "Assets.h"

sf::Texture Assets::PLAYER_TEXTURE;
sf::Texture Assets::PLAYER_RUN;
sf::Texture Assets::PLAYER_FIRE;
sf::Texture Assets::PLAYER_HURT;
sf::Texture Assets::PLAYER_DIE;

sf::Texture Assets::ENEMY_RUN;
sf::Texture Assets::SHOOT_ENEMY;
sf::Texture Assets::TANKER_RUN;

sf::Texture Assets::GEM_TYPE1;
sf::Texture Assets::GEM_TYPE2;
sf::Texture Assets::GEM_TYPE3;

sf::Texture Assets::HEALTH_TYPE1;
sf::Texture Assets::HEALTH_TYPE2;

sf::Texture Assets::SHIELD;

sf::Texture	Assets::SPEED;

sf::Texture Assets::ENEMY_BULLET;
void Assets::init()
{
	if (!PLAYER_TEXTURE.loadFromFile("./Assets/player/newPlayer_IDLE.png")) {
		std::cerr << "[ERROR] Failed to load PLAYER_TEXTURE from './Assets/player/newPlayer_IDLE.png'\n";
	}
	if (!PLAYER_RUN.loadFromFile("./Assets/player/newPlayer_RUN.png")) {
		std::cerr << "[ERROR] Failed to load PLAYER_RUN from './Assets/player/newPlayer_RUN.png'\n";
	}
	if (!PLAYER_FIRE.loadFromFile("./Assets/player/newPlayer_FIRE(2).png")) {
		std::cerr << "[ERROR] Failed to load PLAYER_FIRE from './Assets/player/newPlayer_FIRE.png'\n";
	}

	if (!PLAYER_HURT.loadFromFile("./Assets/player/newPlayer_HURT.png"))
	{
		std::cerr << "[ERROR] Failed to load PLAYER_HURT from './Assets/player/newPlayerHURT.png'\n";
	}

	if (!PLAYER_DIE.loadFromFile("./Assets/player/newPlayer_DIE.png"))
	{
		std::cerr << "[ERROR] Failed to load PLAYER_DIE from './Assets/player/newPlayerDIE.png'\n";
	}

	if (!ENEMY_RUN.loadFromFile("./Assets/enemy/enemy_run.png")) {
		std::cerr << "[ERROR] Failed to load enemy_run from './Assets/enemy/enemy_run.png'\n";
	}

	if (!SHOOT_ENEMY.loadFromFile("./Assets/enemy/shooter_run.png")) {
		std::cerr << "[ERROR] Failed to load shoot_enemy from './Assets/enemy/shooter_run.png'\n";
	}

	if (!GEM_TYPE1.loadFromFile("./Assets/gem/gem_type1.png")) {
		std::cerr << "[ERROR] Failed to load gem from './Assets/gem/gem_type1.png'\n";
	}

	if (!GEM_TYPE2.loadFromFile("./Assets/gem/gem_type2.png")) {
		std::cerr << "[ERROR] Failed to load gem from './Assets/gem/gem_type2.png'\n";
	}

	if (!GEM_TYPE3.loadFromFile("./Assets/gem/gem_type3.png")) {
		std::cerr << "[ERROR] Failed to load gem from './Assets/gem/gem_type3.png'\n";
	}

	if (!HEALTH_TYPE1.loadFromFile("./Assets/powerUp/health_type1.png")) {
		std::cerr << "[ERROR] Failed to load heal from './Assets/gem/health_tyoe1.png'\n";
	}

	if (!HEALTH_TYPE2.loadFromFile("./Assets/powerUp/health_type2.png")) {
		std::cerr << "[ERROR] Failed to load heal from './Assets/gem/health_type2.png'\n";
	}

	if (!SHIELD.loadFromFile("./Assets/powerUp/shield.png")) {
		std::cerr << "[ERROR] Failed to load shield from './Assets/powerUp/shield.png'\n";
	}

	if (!SPEED.loadFromFile("./Assets/powerUp/speed.png")) {
		std::cerr << "[ERROR] Failed to load speed from './Assets/powerUp/speed.png'\n";
	}

	if (!ENEMY_BULLET.loadFromFile("./Assets/bullet/enemy_bullet.png")) {
		std::cerr << "[ERROR] Failed to load enemy_bullet from './Assets/bullet/enemy_bullet.png'\n";
	}

	if(!TANKER_RUN.loadFromFile("./Assets/enemy/tanker_run.png")) {
		std::cerr << "[ERROR] Failed to load tank_run from './Assets/tank/tanker_run.png'\n";
	}
}
