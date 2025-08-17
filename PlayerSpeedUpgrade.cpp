#include "PlayerSpeedUpgrade.h"
void PlayerSpeedUpgrade::upgrade()
{
        if (level < maxLevel) {
            level++;
            applyUpgrade();
        }
}

int PlayerSpeedUpgrade::getLevel() const
{
    return level;
}

void PlayerSpeedUpgrade::applyUpgrade()
{
    auto move = owner->getComponent<KeyboardMove>();
    if (move) {
        move->setSpeed(move->getSpeed() + speedPerLevel);
    }
}