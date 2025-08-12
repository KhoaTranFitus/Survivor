#include "BossShoot.h"
#include "GameManager.h"
#include "MoveForward.h"
#include "DamageOnContact.h"
#include "GameObjectFactory.h"

BossShoot::BossShoot(std::shared_ptr<GameObject> owner, float cooldown)
    : Component(owner), cooldown(cooldown), elapsed(0.f), firing(false), fireAnimTimer(0.f) {}

void BossShoot::update(float deltaTime)
{
    // Nếu đang trong thời gian animation FIRE thì duy trì state FIRE
    if (fireAnimTimer > 0.f && owner) {
        fireAnimTimer -= deltaTime;
        if (fireAnimTimer <= 0.f) {
            // Chỉ quay lại RUN nếu không phải DIE
            if (owner->getCurrentState() != 2)
                owner->setState(0);
        } else {
            owner->setState(1); // Đảm bảo vẫn ở FIRE
        }
    }

    firing = false;
    elapsed += deltaTime;

    if (elapsed >= cooldown)
    {
        elapsed = 0.f;
        firing = true;

        // Set state FIRE khi bắn
        if (owner && owner->getCurrentState() != 2) { // Không set FIRE nếu đang DIE
            owner->setState(1); // FIRE
            fireAnimTimer = fireAnimDuration;
        }

        sf::Vector2f origin = owner->getOrigin();
        sf::Vector2f target = GameManager::getInstance().currentPlayer->getOrigin();
        float angleToPlayer = std::atan2(target.y - origin.y, target.x - origin.x);
        float spread = 20.0f * 3.14159265f / 180.0f; // 20 degrees in radians

        for (int i = -1; i <= 1; ++i)
        {
            float angle = angleToPlayer + i * spread;
            sf::Vector2f dir(std::cos(angle), std::sin(angle));
            sf::Vector2f bulletTarget = origin + dir * 100.f;

            sf::Vector2f bulletSize(20.f, 10.f);
            auto bullet = GameObjectFactory::createBullet(owner->getOrigin(), bulletSize, "boss_bullet");
            bullet->getHitbox().setFillColor(sf::Color::Yellow);

            // Tính góc quay theo độ
            float angleDeg = angle * 180.f / 3.14159265f;

            // Đặt origin về tâm trước khi quay
            bullet->getHitbox().setOrigin(bullet->getHitbox().getSize() / 2.f);
            bullet->getHitbox().setRotation(angleDeg);

            // Chỉ quay animation nếu player ở bên trái boss
            if (bullet->animations) {
                bullet->animations->setCenter();
                if (target.x < origin.x) {
                    bullet->animations->setRotation(angleDeg);
                } else {
                    bullet->animations->setRotation(0.f); // hoặc giữ nguyên góc mặc định
                }
            }

            bullet->addComponent(std::make_shared<MoveForward>(bullet, bulletTarget, 350.f));
            bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "player"));

            GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
        }
    }
}