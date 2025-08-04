#pragma once
#include "Component.h"
#include <memory>
#include "GameObject.h"
#include "stat.h"

class PlayerHealthUpgrade : public Component {
    int level = 1;
    const int maxLevel = 5;
    float healthPerLevel = 20.f;
public:
    PlayerHealthUpgrade(std::shared_ptr<GameObject> owner) : Component(owner) {
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
        auto stat = owner->getComponent<Stat>();
        if (stat) {
            stat->setHealth(stat->getHealth() + healthPerLevel);
            // Optionally increase maxHealth
        }
    }
};

