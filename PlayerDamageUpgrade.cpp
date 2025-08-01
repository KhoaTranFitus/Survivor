#include "PlayerDamageUpgrade.h"
#include "Stat.h"
#include "GameObject.h"


PlayerDamageUpgrade::PlayerDamageUpgrade(std::shared_ptr<GameObject> owner)
    : Component(owner) {}

void PlayerDamageUpgrade::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    auto stat = other->getComponent<Stat>();
    if (stat) {
        stat->upgradeBaseDamage();
        owner->needDeleted = true;
    }
}
