
#pragma once

#include "Component.h"

class PlayerShoot : public Component {
    float cooldown;
    float elapsed;
    float fireAnimTimer = 0.f;
    float fireAnimDuration = 0.2f;
    float range;
public:

    bool isFiring = false; // Biến trạng thái bắn

    PlayerShoot(std::shared_ptr<GameObject> owner, float cooldown, float range);
    void update(float deltaTime) override;

    float getCooldown() const { return cooldown; }
    void setCooldown(float value) { cooldown = value; }
};