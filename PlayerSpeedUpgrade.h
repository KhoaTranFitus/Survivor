#pragma once
#include "Component.h"

class PlayerSpeedUpgrade : public Component
{
public:
    PlayerSpeedUpgrade(std::shared_ptr<GameObject> owner);
    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override {}
};