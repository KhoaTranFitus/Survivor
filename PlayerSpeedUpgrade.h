#pragma once
#include "Component.h"
#include <memory>
#include "GameObject.h"
#include "KeyboardMove.h"

class PlayerSpeedUpgrade : public Component {
    int level = 1;
    const int maxLevel = 5;
    float speedPerLevel = 20.f;
public:
    PlayerSpeedUpgrade(std::shared_ptr<GameObject> owner) : Component(owner) {
        applyUpgrade();
    }
    void upgrade();
    int getLevel() const;
    void update(float deltaTime) override {}
private:
    void applyUpgrade();
};

