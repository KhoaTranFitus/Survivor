#include "PlayerHealthUpgrade.h"
#include "Stat.h"
#include "GameObject.h"


PlayerHealthUpgrade::PlayerHealthUpgrade(std::shared_ptr<GameObject> owner)
    : Component(owner) {}

void PlayerHealthUpgrade::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    auto stat = other->getComponent<Stat>();
    if (stat) {
        stat->upgradeBaseHealth();
        owner->needDeleted = true;
    }
}
