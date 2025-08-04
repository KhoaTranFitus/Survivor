#include "BossShoot.h"
#include "GameManager.h"
#include "MoveForward.h"
#include "DamageOnContact.h"
#include "GameObjectFactory.h"

BossShoot::BossShoot(std::shared_ptr<GameObject> owner, float cooldown)
    : Component(owner), cooldown(cooldown), elapsed(0.f) {}

void BossShoot::update(float deltaTime)
{
    elapsed += deltaTime;

    if (elapsed >= cooldown)
    {
        elapsed = 0.f;

        sf::Vector2f origin = owner->getOrigin();
        sf::Vector2f target = GameManager::getInstance().currentPlayer->getOrigin();
        float angleToPlayer = std::atan2(target.y - origin.y, target.x - origin.x);
        float spread = 20.0f * 3.14159265f / 180.0f; // 20 degrees in radians

        for (int i = -1; i <= 1; ++i)
        {
            float angle = angleToPlayer + i * spread;
            sf::Vector2f dir(std::cos(angle), std::sin(angle));
            sf::Vector2f bulletTarget = origin + dir * 100.f;

            sf::Vector2f bulletSize(30.f, 30.f);
            auto bullet = GameObjectFactory::createBullet(owner->getOrigin(), bulletSize,"boss_bullet");

            bullet->getHitbox().setFillColor(sf::Color::Yellow);
            bullet->addComponent(std::make_shared<MoveForward>(bullet, bulletTarget, 350.f));
            bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "player"));
            GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
        }
    }
}