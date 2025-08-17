#include "PlayerReloadUpgrade.h"

void PlayerReloadUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        applyUpgrade();
    }
}
int PlayerReloadUpgrade::getLevel() const {
    return level;
}

void PlayerReloadUpgrade::applyUpgrade() {
    auto shoot = owner->getComponent<PlayerShoot>();
    if (shoot) {
        shoot->setCooldown(shoot->getCooldown() + reloadPerLevel);
    }
}