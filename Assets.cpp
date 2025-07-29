#include "Assets.h"

sf::Texture Assets::PLAYER_TEXTURE;
sf::Texture Assets::PLAYER_RUN;

void Assets::init()
{
	if (!PLAYER_TEXTURE.loadFromFile("./Assets/player/player_IDLE.png")) {
		std::cerr << "[ERROR] Failed to load PLAYER_TEXTURE from './Assets/player/player_IDLE.png'\n";
	}

	if (!PLAYER_RUN.loadFromFile("./Assets/player/player_RUN.png")) {

		std::cerr << "[ERROR] Failed to load PLAYER_RUN from './Assets/player/player_RUN.png'\n";
	}
}
