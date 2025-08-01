#include "Assets.h"

sf::Texture Assets::PLAYER_TEXTURE;
sf::Texture Assets::PLAYER_RUN;
sf::Texture Assets::PLAYER_FIRE;
sf::Texture Assets::ENEMY_RUN;

void Assets::init()
{
	if (!PLAYER_TEXTURE.loadFromFile("./Assets/player/newPlayer_IDLE.png")) {
		std::cerr << "[ERROR] Failed to load PLAYER_TEXTURE from './Assets/player/newPlayer_IDLE.png'\n";
	}
	if (!PLAYER_RUN.loadFromFile("./Assets/player/newPlayer_RUN.png")) {
		std::cerr << "[ERROR] Failed to load PLAYER_RUN from './Assets/player/newPlayer_RUN.png'\n";
	}
	if(!PLAYER_FIRE.loadFromFile("./Assets/player/newPlayer_FIRE.png")) {
		std::cerr << "[ERROR] Failed to load PLAYER_FIRE from './Assets/player/newPlayer_FIRE.png'\n";
	}
	if(!ENEMY_RUN.loadFromFile("./Assets/enemy/enemy_run.png")) {
		std::cerr << "[ERROR] Failed to load enemy_run from './Assets/enemy/enemy_run.png'\n";
	}
}
