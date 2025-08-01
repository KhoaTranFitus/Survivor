#pragma once
#include "Component.h"

class PlayerReloadUpgrade : public Component
{
public:
    PlayerReloadUpgrade(std::shared_ptr<GameObject> owner);
    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override {}
};

