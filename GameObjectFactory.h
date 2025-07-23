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

class GameObjectFactory
{
public:
	static std::shared_ptr<Player> createPlayer();

	static std::shared_ptr<GameObject> createBackground(const std::string& path);
	static std::shared_ptr<Enemies> createEnemy();
	static std::shared_ptr<Bullet> createBullet(sf::Vector2f position);

};

// cái này là Factory Pattern ?? t?o ra các ??i t??ng GameObject