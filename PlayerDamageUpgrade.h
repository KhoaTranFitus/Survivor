#pragma once
#include "Component.h"
#include <memory>
#include "Stat.h"
#include "GameObject.h"

class PlayerDamageUpgrade : public Component {
private:
    int level = 1;
    const int maxLevel = 5;
    float damagePerLevel = 5.f;
    void applyUpgrade();
public:
    PlayerDamageUpgrade(std::shared_ptr<GameObject> owner) : Component(owner) {
        applyUpgrade();
    }
    void upgrade();
    int getLevel() const { return level; }
    void update(float deltaTime) override {}
};

