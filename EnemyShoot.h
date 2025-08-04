#pragma once
#include "Component.h"
#include <memory>

class EnemyShoot : public Component {
    float cooldown;
    float elapsed;
public:
    EnemyShoot(std::shared_ptr<GameObject> owner, float cooldown);
    void update(float deltaTime) override;
};