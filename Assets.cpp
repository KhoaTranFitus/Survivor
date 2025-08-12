#include "Assets.h"

sf::Texture Assets::PLAYER_TEXTURE;
sf::Texture Assets::PLAYER_RUN;
sf::Texture Assets::PLAYER_FIRE;
sf::Texture Assets::PLAYER_HURT;
sf::Texture Assets::PLAYER_DIE;

sf::Texture Assets::ENEMY_RUN;
sf::Texture Assets::SHOOT_ENEMY;
sf::Texture Assets::TANKER_RUN;
sf::Texture Assets::DASH_RUN;

sf::Texture Assets::BOSS_RUN;
sf::Texture Assets::BOSS_FIRE;
sf::Texture Assets::BOSS_DIE;

sf::Texture Assets::GEM_TYPE1;
sf::Texture Assets::GEM_TYPE2;
sf::Texture Assets::GEM_TYPE3;

sf::Texture Assets::HEALTH_TYPE1;
sf::Texture Assets::HEALTH_TYPE2;

sf::Texture Assets::SHIELD;

sf::Texture	Assets::SPEED;

sf::Texture Assets::ENEMY_BULLET;
sf::Texture Assets::BOSS_BULLET;

sf::SoundBuffer Assets::GEM_PICKUP_S;
sf::Sound Assets::GEM_PICKUP_SOUND;
sf::SoundBuffer Assets::POWERUP_PICKUP_S;
sf::Sound Assets::POWERUP_PICKUP_SOUND;

sf::SoundBuffer Assets::PLAYER_HURT_S;
sf::Sound Assets::PLAYER_HURT_SOUND;



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
	if(!DASH_RUN.loadFromFile("./Assets/enemy/dash_run.png")) {
		std::cerr << "[ERROR] Failed to load dash_run from './Assets/enemy/dash_run.png'\n";
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
	if (!BOSS_BULLET.loadFromFile("./Assets/bullet/boss_bullet.png")) {
		std::cerr << "[ERROR] Failed to load boss_bullet from './Assets/bullet/boss_bullet.png'\n";
	}

	if (!TANKER_RUN.loadFromFile("./Assets/enemy/tanker_run.png")) {
		std::cerr << "[ERROR] Failed to load tank_run from './Assets/tank/tanker_fire.png'\n";
	}

	if (!BOSS_RUN.loadFromFile("./Assets/enemy/boss_run.png"))
	{
		std::cerr << "[ERROR] Failed to load boss_run from './Assets/enemy/boss_run.png'\n";
	}
	if (!BOSS_FIRE.loadFromFile("./Assets/enemy/boss_fire.png"))
	{
		std::cerr << "[ERROR] Failed to load boss_fire from './Assets/enemy/boss_fire.png'\n";
	}
	if (!BOSS_DIE.loadFromFile("./Assets/enemy/boss_die.png"))
	{
		std::cerr << "[ERROR] Failed to load boss_die from './Assets/enemy/boss_die.png'\n";
	}
	

	// add sound for game

	if(!GEM_PICKUP_S.loadFromFile("./Assets/sound/gem_pickup.mp3")) {
		std::cerr << "[ERROR] Failed to load GEM_PICKUP sound from './Assets/sound/gem_pickup.wav'\n";
	}
	GEM_PICKUP_SOUND.setBuffer(GEM_PICKUP_S);

	if(!POWERUP_PICKUP_S.loadFromFile("./Assets/sound/powerup_pickup.wav")) {
		std::cerr << "[ERROR] Failed to load POWERUP_PICKUP sound from './Assets/sound/powerup_pickup.wav'\n";
	}
	POWERUP_PICKUP_SOUND.setBuffer(POWERUP_PICKUP_S);

	if(!PLAYER_HURT_S.loadFromFile("./Assets/sound/player_hurt.wav")) {
		std::cerr << "[ERROR] Failed to load PLAYER_HURT sound from './Assets/sound/player_hurt.wav'\n";
	}
	PLAYER_HURT_SOUND.setBuffer(PLAYER_HURT_S);
}
