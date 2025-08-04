
#pragma once

#include "Component.h"

class PlayerShoot : public Component {
    float cooldown;
    float elapsed;
    float fireAnimTimer = 0.f;
    float fireAnimDuration = 0.2f;
public:

    bool isFiring = false; // Biến trạng thái bắn

    PlayerShoot(std::shared_ptr<GameObject> owner, float cooldown);
    void update(float deltaTime) override;

    float getCooldown() const { return cooldown; }
    void setCooldown(float value) { cooldown = value; }
};