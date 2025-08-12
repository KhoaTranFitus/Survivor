#pragma once
#include "Component.h"
#include <memory>

class BossShoot : public Component {
    float cooldown;
    float elapsed;
    bool firing;
    float fireAnimTimer = 0.f;
    const float fireAnimDuration = 0.5f; // thời gian animation FIRE (giây)
public:
    BossShoot(std::shared_ptr<GameObject> owner, float cooldown);
    void update(float deltaTime) override;

    bool isFiring() const { return firing; }
};