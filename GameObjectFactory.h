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
	static std::shared_ptr<Enemies> createTankerEnemy();
	static std::shared_ptr<Enemies> createBurstEnemy();
	static std::shared_ptr<Enemies> createDashEnemy();


	static std::shared_ptr<Enemies> createShooterEnemy();
	static std::shared_ptr<Enemies> createBoss();

	static std::shared_ptr<Bullet> createBullet(sf::Vector2f position, sf::Vector2f size, const std::string& tag);
	static std::shared_ptr<PowerUp> createPowerUp(std::string name, float x, float y);
	static std::shared_ptr<GameObject> createGem(float x, float);
};

// cái này là Factory Pattern ?? t?o ra các ??i t??ng GameObject