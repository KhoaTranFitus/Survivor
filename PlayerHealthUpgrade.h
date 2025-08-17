#pragma once
#include "Component.h"
#include <memory>
#include "GameObject.h"
#include "stat.h"

class PlayerHealthUpgrade : public Component {
private:
    int level = 1;
    const int maxLevel = 5;
    float healthPerLevel = 20.f;
    void applyUpgrade();
public:
    PlayerHealthUpgrade(std::shared_ptr<GameObject> owner) : Component(owner) {
        applyUpgrade();
    }
    void upgrade();
    int getLevel() const;
    void update(float deltaTime) override {}
};

