#include "PlayerHealthUpgrade.h"

void PlayerHealthUpgrade::applyUpgrade ()
{
    auto stat = owner->getComponent<Stat>();
    if (stat) {
        stat->setHealth(stat->getHealth() + healthPerLevel);
    }
}

void PlayerHealthUpgrade::upgrade()
{
    if (level < maxLevel) {
        level++;
        applyUpgrade();
    }
}

int PlayerHealthUpgrade::getLevel() const
{
    return level;
}