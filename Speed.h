#pragma once
#include "Component.h"

class Speed : public Component
{
    float percent; // phần trăm tăng tốc (vd: 0.3f là 30%)

public:
    Speed(std::shared_ptr<GameObject> owner, float percent);

    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override {}
};

