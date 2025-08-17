#include "PlayerDamageUpgrade.h"


void PlayerDamageUpgrade::applyUpgrade() {
    auto stat = owner->getComponent<Stat>();
    if (stat) {
        stat->setDamage(stat->getDamage() + damagePerLevel);
    }
}

void PlayerDamageUpgrade::upgrade() {
    if (level < maxLevel) {
        level++;
        applyUpgrade();
    }
    // Nếu đã max level thì không làm gì
}