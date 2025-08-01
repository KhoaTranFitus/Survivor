#pragma once
#include "Component.h"

class Shield : public Component
{
    float shieldAmount;

public:
    Shield(std::shared_ptr<GameObject> owner, float shieldAmount);

    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override {}
};

