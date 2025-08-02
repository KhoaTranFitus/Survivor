#include "EnemyShoot.h"
#include "GameManager.h"
#include "MoveForward.h"
#include "DamageOnContact.h"
#include "GameObjectFactory.h"

EnemyShoot::EnemyShoot(std::shared_ptr<GameObject> owner, float cooldown)
    : Component(owner), cooldown(cooldown), elapsed(0.f) {}

void EnemyShoot::update(float deltaTime)
{
    elapsed += deltaTime;

    if (elapsed >= cooldown)
    {
        elapsed = 0.f;

        sf::Vector2f size(10.f, 10.f);
        auto bullet = GameObjectFactory::createBullet(owner->getOrigin(), size);
        bullet->getHitbox().setFillColor(sf::Color::Red);
        bullet->addComponent(std::make_shared<MoveForward>(bullet, GameManager::getInstance().currentPlayer->getOrigin(), 300.f));
        bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "player"));
        GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
    }
}