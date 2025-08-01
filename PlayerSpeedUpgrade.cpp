#include "PlayerSpeedUpgrade.h"
#include "Stat.h"
#include "GameObject.h"

PlayerSpeedUpgrade::PlayerSpeedUpgrade(std::shared_ptr<GameObject> owner)
    : Component(owner) {}

void PlayerSpeedUpgrade::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    auto stat = other->getComponent<Stat>();
    if (stat) {
        stat->upgradeBaseSpeed();
        owner->needDeleted = true;
    }
}
