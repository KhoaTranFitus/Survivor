#pragma once
#include "Component.h"
#include <memory>
#include "GameObject.h"
#include "PlayerShoot.h"

class PlayerReloadUpgrade : public Component {
    int level = 1;
    const int maxLevel = 5;
    float reloadPerLevel = -0.05f; // Reduce cooldown
public:
    PlayerReloadUpgrade(std::shared_ptr<GameObject> owner) : Component(owner) {
        applyUpgrade();
    }
    void upgrade() {
        if (level < maxLevel) {
            level++;
            applyUpgrade();
        }
    }
    int getLevel() const { return level; }
    void update(float deltaTime) override {}
private:
    void applyUpgrade() {
        auto shoot = owner->getComponent<PlayerShoot>();
        if (shoot) {
            shoot->setCooldown(shoot->getCooldown() + reloadPerLevel);
        }
    }
};

