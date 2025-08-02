#pragma once
#include "Component.h"
#include "GameObject.h"

class Shield : public Component
{
    float shieldAmount;
    float duration;
    float timer = 0.f;

public:
    Shield(std::shared_ptr<GameObject> owner, float amount, float duration);

    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override;

    float getShield() const { return shieldAmount; }
};
