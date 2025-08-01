#pragma once
#include "Player.h"
#include "Config.h"
#include "KeyboardMove.h"
#include "GameObject.h"
#include "BackGround.h"
#include "Stat.h"
#include "Enemies.h"
#include "FollowTarget.h"
#include "Bullet.h" 
#include "PowerUp.h"
class GameObjectFactory
{
public:
	static std::shared_ptr<Player> createPlayer();

	static std::shared_ptr<GameObject> createBackground(const std::string& path);
	static std::shared_ptr<Enemies> createDefaultEnemy();
	static std::shared_ptr<Bullet> createBullet(sf::Vector2f position,sf::Vector2f size);


	static std::shared_ptr<Enemies> createShooterEnemy();
	static std::shared_ptr<Enemies> createBoss();
	static std::shared_ptr<PowerUp> createPowerUp(std::string name, float x, float y);
	static std::shared_ptr<GameObject> createGem(float x, float y);
};

// cái này là Factory Pattern ?? t?o ra các ??i t??ng GameObject