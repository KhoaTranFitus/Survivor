#pragma once
#include "Component.h"
#include <memory>

class BossShoot : public Component {
    float cooldown;
    float elapsed;
public:
    BossShoot(std::shared_ptr<GameObject> owner, float cooldown);
    void update(float deltaTime) override;
};