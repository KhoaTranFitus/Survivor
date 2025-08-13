#include "GameObjectFactory.h"
#include "GameManager.h"
#include "NoOverlapComponent.h"
#include "Camera.h"
#include "ItemEffect.h"
#include "Gem.h"
#include "PlayerStat.h"
#include "DefaultEnemy.h"
#include "ShooterEnemy.h"
#include "DamageOnContact.h"
#include "Boss.h"
#include "Assets.h"
#include "Bullet.h"
#include "PlayerShoot.h"
#include "EnemyShoot.h"
#include "BossShoot.h"
#include "BurstEnemyShoot.h"
#include "BurstEnemy.h"
#include "TankerEnemy.h"
#include "Heal.h"
#include "Shield.h"
#include "Speed.h"
#include "DashComponent.h"
#include "DashEnemy.h"
#include <random>


static std::vector<std::shared_ptr<GameObject>>* getGameObjectsPtr() {
    auto scene = GameManager::getInstance().getCurrentScene();
    if (scene) return &(scene->getGameObjects());
    return nullptr;
}

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
    auto player = std::make_shared<Player>();

    // Thêm các component cho player
    player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
    player->addComponent(std::make_shared<Stat>(player, 300,20 ));
    player->addComponent(std::make_shared<PlayerStat>(player));
    player->addComponent(std::make_shared<PlayerShoot>(player, 0.35f, 500.f)); // cooldown, range
    GameManager::getInstance().currentPlayer = player;
    return player;
}

std::shared_ptr<GameObject> GameObjectFactory::createBackground(const std::string& path)
{
    return std::make_shared<Background>(path);
}



std::shared_ptr<Enemies> GameObjectFactory::createDefaultEnemy() {
    auto enemy = std::make_shared<DefaultEnemy>();
    enemy->setTag("enemies");
    enemy->addComponent(std::make_shared<NoOverlapComponent>(enemy, getGameObjectsPtr()));
    enemy->addComponent(std::make_shared<FollowTarget>(enemy, GameManager::getInstance().currentPlayer, 100.f));
    enemy->addComponent(std::make_shared<Stat>(enemy, 100, 5));
    enemy->addComponent(std::make_shared<DamageOnContact>(enemy, enemy->getComponent<Stat>()->getDamage(), "player", 1.0f));
    // Không có Shoot
    return enemy;
}

std::shared_ptr<Enemies> GameObjectFactory::createTankerEnemy() {
    auto enemy = std::make_shared<TankerEnemy>();
    enemy->setTag("enemies");
    enemy->addComponent(std::make_shared<NoOverlapComponent>(enemy, getGameObjectsPtr()));
    enemy->addComponent(std::make_shared<FollowTarget>(enemy, GameManager::getInstance().currentPlayer, 100.f));
    enemy->addComponent(std::make_shared<Stat>(enemy, 300, 5));
    enemy->addComponent(std::make_shared<DamageOnContact>(enemy, enemy->getComponent<Stat>()->getDamage(), "player", 1.0f));
    // Không có Shoot
    return enemy;
}

std::shared_ptr<Enemies> GameObjectFactory::createShooterEnemy() {
    auto enemy = std::make_shared<ShooterEnemy>();
    enemy->setTag("enemies");
    enemy->addComponent(std::make_shared<NoOverlapComponent>(enemy, getGameObjectsPtr()));
    enemy->addComponent(std::make_shared<FollowTarget>(enemy, GameManager::getInstance().currentPlayer, 80.f));
    enemy->addComponent(std::make_shared<Stat>(enemy, 50, 10));
    enemy->addComponent(std::make_shared<EnemyShoot>(enemy, 1.5f)); // Có Shoot
    enemy->addComponent(std::make_shared<DamageOnContact>(enemy, enemy->getComponent<Stat>()->getDamage(), "player", 1.0f));
    return enemy;
}

std::shared_ptr<Enemies> GameObjectFactory::createBurstEnemy() {
    auto enemy = std::make_shared<BurstEnemy>();
    enemy->setTag("enemies");
    enemy->addComponent(std::make_shared<NoOverlapComponent>(enemy, getGameObjectsPtr()));
    enemy->addComponent(std::make_shared<FollowTarget>(enemy, GameManager::getInstance().currentPlayer, 80.f));
    enemy->addComponent(std::make_shared<Stat>(enemy, 50, 7));
    enemy->addComponent(std::make_shared<BurstEnemyShoot>(enemy, 3.0f, 3)); // 3 bullets per burst
    enemy->addComponent(std::make_shared<DamageOnContact>(enemy, enemy->getComponent<Stat>()->getDamage(), "player", 1.0f));
    return enemy;
}


std::shared_ptr<Enemies> GameObjectFactory::createDashEnemy() {
    auto enemy = std::make_shared<DashEnemy>();
    enemy->setTag("enemies");
    enemy->addComponent(std::make_shared<NoOverlapComponent>(enemy, getGameObjectsPtr()));
    enemy->addComponent(std::make_shared<DashComponent>(enemy, 3.5f, 80.f, 800.f, 0.3f, 1.f)); // moveTime, moveSpeed, dashSpeed, dashDuration, waitTime
    enemy->addComponent(std::make_shared<Stat>(enemy, 80, 5));
    enemy->addComponent(std::make_shared<DamageOnContact>(enemy, enemy->getComponent<Stat>()->getDamage(), "player", 1.0f));
    return enemy;
}

std::shared_ptr<Enemies> GameObjectFactory::createBoss()
{
    auto boss = std::make_shared<Boss>();
    boss->setTag("boss");
    boss->addComponent(std::make_shared<Stat>(boss, 500,20)); // Máu và damage lớn hơn
    boss->addComponent(std::make_shared<BossShoot>(boss, 2.5f)); // Bắn 3 tia đã xử lý trong Shoot
    //boss->addComponent(std::make_shared<DamageOnContact>(boss, boss->getComponent<Stat>()->getDamage(), "player", 1.0f));
    boss->addComponent(std::make_shared<BurstEnemyShoot>(boss, 4.0f, 5)); // 3 bullets per burst
    boss->addComponent(std::make_shared<DashComponent>(boss, 5.f, 80.f, 1000.f, 0.5f, 1.f)); // Boss dash
    return boss;
}

//tạo ra bullet
std::shared_ptr<Bullet> GameObjectFactory::createBullet(sf::Vector2f position, sf::Vector2f size, const std::string& tag)
{
    auto bullet = std::make_shared<Bullet>(position, size, tag);
    bullet->setTag(tag);
    return bullet;
}
std::shared_ptr<PowerUp> GameObjectFactory::createPowerUp(std::string name, float x, float y)
{
    // Factory only manages, delegates creation to PowerUp
    return PowerUp::Create(name, x, y);
}

std::shared_ptr<GameObject> GameObjectFactory::createGem(float x, float y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 99);
    int r = dist(gen);

    std::string tag;
    int exp;
    if (r < 70) {
        tag = "gem_type1";
        exp = 10;
    } else if (r < 90) {
        tag = "gem_type2";
        exp = 30;
    } else {
        tag = "gem_type3";
        exp = 50;
    }

    auto gem = std::make_shared<Gem>(sf::Vector2f(x, y), tag);
    gem->addComponent(std::make_shared<ItemEffect>(
        gem,
        [exp](std::shared_ptr<GameObject> target) {
            auto playerStat = target->getComponent<PlayerStat>();
            if (playerStat) {
                playerStat->addExp(exp);
            }
            return nullptr;
        }
    ));
    return gem;
}
