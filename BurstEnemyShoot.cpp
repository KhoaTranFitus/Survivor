#include "BurstEnemyShoot.h"
#include "GameManager.h"
#include "MoveForward.h"
#include "DamageOnContact.h"
#include "GameObjectFactory.h"

BurstEnemyShoot::BurstEnemyShoot(std::shared_ptr<GameObject> owner, float cooldown, int burstCount)
    : Component(owner), cooldown(cooldown), elapsed(0.f), burstCount(burstCount), burstElapsed(0.f), burstFired(0) {}

void BurstEnemyShoot::update(float deltaTime)
{
    elapsed += deltaTime;

    if (elapsed >= cooldown)
    {
        burstElapsed += deltaTime;

        if (burstFired < burstCount && burstElapsed >= 0.1f) // Fire every 0.1 seconds
        {
            burstElapsed = 0.f;
            burstFired++;

            sf::Vector2f size(10.f, 10.f);
            auto bullet = GameObjectFactory::createBullet(owner->getOrigin(), size,"shoot_bullet");
            bullet->getHitbox().setFillColor(sf::Color::Blue);
            bullet->addComponent(std::make_shared<MoveForward>(bullet, GameManager::getInstance().currentPlayer->getOrigin(), 400.f));
            bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "player"));
            GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
        }

        if (burstFired >= burstCount)
        {
            elapsed = 0.f;
            burstFired = 0;
        }
    }
}