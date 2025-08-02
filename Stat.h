#pragma once
#include "Component.h"
#include <memory>

class Stat : public Component {
private:
    float health;
    float maxHealth;
    float shield;
    float baseSpeed;
    float damage;
    float reloadSpeed = 1.f; // thời gian giữa mỗi lần bắn, đơn vị: giây


public:
    Stat(std::shared_ptr<GameObject> owner, float health, float damage, float speed);

    int damageUpgradeLevel = 0;
    int healthUpgradeLevel = 0;
    int speedUpgradeLevel = 0;
    int reloadUpgradeLevel = 0;

    float getHealth() const;
    float getMaxHealth() const;
    float getDamage() const;
    float getBaseSpeed() const;
    float getCurrentSpeed() const;

    void takeDamage(float amount);
    void modifySpeed(float delta);       // tăng giảm tốc độ tạm thời
    void modifyShield(float delta);      // tăng giảm khiên tạm thời
    void heal(float amount);             // hồi máu
    void upgradeBaseDamage(float amount = PLAYER_DAMAGE); // tăng sát thương vĩnh viễn
    void upgradeBaseSpeed(float amount = PLAYER_SPEED * 0.3f);
    void upgradeBaseHealth();
    void upgradeBaseReload(float amount = -0.2f);
    void update(float deltaTime) override {}

};
