#pragma once
#include "GameObjectFactory.h"
#include "GameManager.h"
#include "Camera.h"
#include "Shoot.h"
//#include "Assets.h"

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
    auto player = std::make_shared<Player>();

    // bật tắt tùy ý các hành vi (component)
    player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
    //player->addComponent(std::make_shared<Stat>(player, 100, 20));
    player->addComponent(std::make_shared<Shoot>(player, 0.75f));

    GameManager::getInstance().currentPlayer = player;
    return player;
}

std::shared_ptr<GameObject> GameObjectFactory::createBackground(const std::string& path)
{
    return std::make_shared<Background>(path);
}

std::shared_ptr<Enemies> GameObjectFactory::createEnemy()
{
    if (!GameManager::getInstance().currentPlayer)
    {
        std::cerr << "[ERROR] Cannot create enemy: player is null\n";
        return nullptr;
    }
	auto enemies = std::make_shared<Enemies>();
	enemies->setTag("enemies");

	enemies->addComponent(std::make_shared<FollowTarget>(enemies, GameManager::getInstance().currentPlayer, 100.f));
    enemies->addComponent(std::make_shared<Stat>(enemies, 100, 20));
    enemies->addComponent(std::make_shared<Shoot>(enemies, 0.75f));

    return enemies;
}

std::shared_ptr<Bullet> GameObjectFactory::createBullet(sf::Vector2f position)
{
	auto bullet = std::make_shared<Bullet>(position);

	return bullet;
}