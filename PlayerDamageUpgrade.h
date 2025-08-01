#pragma once
#include "Component.h"

class PlayerDamageUpgrade : public Component
{
public:
    PlayerDamageUpgrade(std::shared_ptr<GameObject> owner);
    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override {}
};

