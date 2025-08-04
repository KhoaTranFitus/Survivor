#pragma once

#include "Component.h"

class PlayerShoot : public Component {
    float cooldown;
    float elapsed;
    float fireAnimTimer = 0.f;
    float fireAnimDuration = 0.2f;
public:
    bool isFiring = false; // Bi?n tr?ng thái b?n

    PlayerShoot(std::shared_ptr<GameObject> owner, float cooldown);
    void update(float deltaTime) override;
};