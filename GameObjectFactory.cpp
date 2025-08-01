#pragma once
#include "GameObjectFactory.h"
#include "GameManager.h"
#include "Camera.h"
#include "Shoot.h"
#include "ItemEffect.h"
#include "Gem.h"
#include "PlayerStat.h"
#include "DefaultEnemy.h"
#include "ShooterEnemy.h"
#include "DamageOnContact.h"
#include "Boss.h"

//change here

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
    auto player = std::make_shared<Player>();

    // Thêm các component cho player
    player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
    player->addComponent(std::make_shared<Stat>(player, 10000, 20));
    player->addComponent(std::make_shared<PlayerStat>(player));

    //player->addComponent(std::make_shared<Shoot>(player, 0.75f));
    player->addComponent(std::make_shared<Shoot>(player, 0.75f));

    GameManager::getInstance().currentPlayer = player;
    return player;
}

std::shared_ptr<GameObject> GameObjectFactory::createBackground(const std::string& path)
{
    return std::make_shared<Background>(path);
}
//tạo default enemy
//std::shared_ptr<Enemies> GameObjectFactory::createEnemy()
//{
//    if (!GameManager::getInstance().currentPlayer)
//    {
//        std::cerr << "[ERROR] Cannot create enemy: player is null\n";
//        return nullptr;
//    }
//	auto enemies = std::make_shared<Enemies>();
//	enemies->setTag("enemies");
//
//	enemies->addComponent(std::make_shared<FollowTarget>(enemies, GameManager::getInstance().currentPlayer, 100.f));
//    enemies->addComponent(std::make_shared<Stat>(enemies, 100, 20));
//    enemies->addComponent(std::make_shared<Shoot>(enemies, 1.f));
//
//    return enemies;
//}

std::shared_ptr<Enemies> GameObjectFactory::createDefaultEnemy()
{
    auto enemy = std::make_shared<DefaultEnemy>();
    enemy->setTag("enemies");
    enemy->addComponent(std::make_shared<FollowTarget>(enemy, GameManager::getInstance().currentPlayer, 100.f));
    enemy->addComponent(std::make_shared<Stat>(enemy, 100, 20));
    enemy->addComponent(std::make_shared<DamageOnContact>(enemy, enemy->getComponent<Stat>()->getDamage(), "player", 1.0f));
    // Không có Shoot
    return enemy;
}

std::shared_ptr<Enemies> GameObjectFactory::createShooterEnemy()
{
    auto enemy = std::make_shared<ShooterEnemy>();
    enemy->setTag("enemies");
    enemy->addComponent(std::make_shared<FollowTarget>(enemy, GameManager::getInstance().currentPlayer, 80.f));
    enemy->addComponent(std::make_shared<Stat>(enemy, 100, 20));
    enemy->addComponent(std::make_shared<Shoot>(enemy, 1.5f)); // Có Shoot
    enemy->addComponent(std::make_shared<DamageOnContact>(enemy, enemy->getComponent<Stat>()->getDamage(), "player", 1.0f));
    return enemy;
}


//tạo ra bullet
std::shared_ptr<Bullet> GameObjectFactory::createBullet(sf::Vector2f position)
{
	auto bullet = std::make_shared<Bullet>(position);
    bullet->setTag("bullet");

	return bullet;
}
// tạo ra enemy bắn được sau 1 khoảng thời gian nhất định, và ít hơn default enemy
//std::shared_ptr<Enemies> GameObjectFactory::createShooterEnemy()
//{
//    return std::shared_ptr<Enemies>();
//}

std::shared_ptr<Enemies> GameObjectFactory::createBoss()
{
    auto boss = std::make_shared<Boss>();
    boss->setTag("boss");
    boss->addComponent(std::make_shared<FollowTarget>(boss, GameManager::getInstance().currentPlayer, 60.f));
    boss->addComponent(std::make_shared<Stat>(boss, 1000, 50)); // Máu và damage lớn hơn
    boss->addComponent(std::make_shared<Shoot>(boss, 1.0f)); // Bắn 3 tia đã xử lý trong Shoot
    boss->addComponent(std::make_shared<DamageOnContact>(boss, boss->getComponent<Stat>()->getDamage(), "player", 1.0f));
    return boss;
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

std::shared_ptr<GameObject> GameObjectFactory::createGem(float x, float y)
{
    auto gem = std::make_shared<Gem>(sf::Vector2f(x, y));
    gem->setTag("gem"); // Đảm bảo tag được set
    gem->addComponent(std::make_shared<ItemEffect>(
        gem,
        [](std::shared_ptr<GameObject> target) {
            auto playerStat = target->getComponent<PlayerStat>();
            if (playerStat) {
                playerStat->addExp(20);
            }
            return nullptr;
        }
    ));
    return gem;
}