#pragma once
#include "Component.h"

class PlayerHealthUpgrade : public Component
{
public:
    PlayerHealthUpgrade(std::shared_ptr<GameObject> owner);
    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override {}
};

