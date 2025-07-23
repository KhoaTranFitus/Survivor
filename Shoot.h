// Shoot.h
#pragma once
#include "Component.h"
#include <vector>
#include <memory>
#include "Bullet.h"
#include "GameManager.h"

class Shoot : public Component
{
private:
    float cooldown;
    float elapsed;

public:
    Shoot(std::shared_ptr<GameObject> owner, float cooldown = 0.75f);

    void update(float deltaTime) override;
};
