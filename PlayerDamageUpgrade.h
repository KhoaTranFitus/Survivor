#pragma once
#include "Component.h"

class PlayerDamageUpgrade : public Component
{
    float bonus;
public:
    PlayerDamageUpgrade(std::shared_ptr<GameObject> owner, float bonus);
    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
};

