#pragma once
#include "Component.h"
#include <memory>
#include "Stat.h"
#include "GameObject.h"

class PlayerDamageUpgrade : public Component {
    int level = 1;
    const int maxLevel = 5;
    float damagePerLevel = 5.f;
public:
    PlayerDamageUpgrade(std::shared_ptr<GameObject> owner) : Component(owner) {
        applyUpgrade();
    }
    void upgrade() {
        if (level < maxLevel) {
            level++;
            applyUpgrade();
        }
        // Nếu đã max level thì không làm gì
    }
    int getLevel() const { return level; }
    void update(float deltaTime) override {}
private:
    void applyUpgrade() {
        auto stat = owner->getComponent<Stat>();
        if (stat) {
            stat->setDamage(stat->getDamage() + damagePerLevel);
        }
    }
};

