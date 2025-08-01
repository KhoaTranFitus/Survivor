#pragma once
#include "Component.h"
#include <memory>
#include <string>

class DamageOnContact : public Component
{
private:
    float damage;
    std::string targetTag;
    float cooldown; // thời gian giữa 2 lần gây damage
    float timer;    // đếm ngược cooldown

public:
    DamageOnContact(std::shared_ptr<GameObject> owner, float damage, std::string targetTag, float cooldown = 1.0f);
    void update(float deltaTime) override;
    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
};