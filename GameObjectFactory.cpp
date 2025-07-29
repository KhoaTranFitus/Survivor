#pragma once
#include "GameObjectFactory.h"
#include "GameManager.h"
#include "Camera.h"
#include "Shoot.h"
#include "ItemEffect.h"
//#include "Heal.h"
//#include "Assets.h"

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
    auto player = std::make_shared<Player>();

    // bật tắt tùy ý các hành vi (component)
    player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
    player->addComponent(std::make_shared<Stat>(player, 100, 20));
    player->addComponent(std::make_shared<Shoot>(player, 0.75f));

    GameManager::getInstance().currentPlayer = player;
    return player;
}

std::shared_ptr<GameObject> GameObjectFactory::createBackground(const std::string& path)
{
    return std::make_shared<Background>(path);
}
//tạo default enemy
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
    enemies->addComponent(std::make_shared<Shoot>(enemies, 1.f));

    return enemies;
}


//tạo ra bullet
std::shared_ptr<Bullet> GameObjectFactory::createBullet(sf::Vector2f position)
{
	auto bullet = std::make_shared<Bullet>(position);
    bullet->setTag("bullet");

	return bullet;
}
// tạo ra enemy bắn được sau 1 khoảng thời gian nhất định, và ít hơn default enemy
std::shared_ptr<Enemies> GameObjectFactory::createShooterEnemy()
{
    return std::shared_ptr<Enemies>();
}

std::shared_ptr<Enemies> GameObjectFactory::createBoss()
{
    return std::shared_ptr<Enemies>();
}

std::shared_ptr<PowerUp> GameObjectFactory::createPowerUp(std::string name, float x, float y)
{
    auto powerUp = std::make_shared<PowerUp>();
    powerUp->setTag("item");
	powerUp->getHitbox().setPosition(x, y);

    if (name == "shoot")
    {
        powerUp->addComponent(std::make_shared<ItemEffect>(
            powerUp,
            [](std::shared_ptr<GameObject> target) {
                return std::make_shared<Shoot>(target, 1.f);
            }
        ));
    }
    else if (name == "move")
    {
		powerUp->getHitbox().setFillColor(sf::Color::Green);
        powerUp->addComponent(std::make_shared<ItemEffect>(
            powerUp,
            [](std::shared_ptr<GameObject> target) {
                return std::make_shared<KeyboardMove>(target, 400.f, "arrows");
            }
        ));
    }
    return powerUp;
}