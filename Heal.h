#pragma once
#include "Component.h"

class Heal : public Component
{
    float healAmount;

public:
    Heal(std::shared_ptr<GameObject> owner, float healAmount);

    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override {}
};