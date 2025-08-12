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
        auto move = owner->getComponent<KeyboardMove>();
        if (move) {
            move->setSpeed(move->getSpeed() + speedPerLevel);
        }
    }
};

