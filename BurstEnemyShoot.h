#pragma once
#include "Component.h"
#include <memory>

class BurstEnemyShoot : public Component {
    float cooldown;
    float elapsed;
    int burstCount;
    int burstFired;
    float burstElapsed;
public:
    BurstEnemyShoot(std::shared_ptr<GameObject> owner, float cooldown, int burstCount);
    void update(float deltaTime) override;
};