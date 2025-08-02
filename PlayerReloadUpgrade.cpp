#include "PlayerReloadUpgrade.h"
#include "Stat.h"
#include "GameObject.h"

PlayerReloadUpgrade::PlayerReloadUpgrade(std::shared_ptr<GameObject> owner)
    : Component(owner) {}

void PlayerReloadUpgrade::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    auto stat = other->getComponent<Stat>();
    if (stat) {
        stat->upgradeBaseReload();
        owner->needDeleted = true;
    }
}
