#pragma once

#include "Component.h"

class Stat : public Component
{
public: // <-- Đổi sang public để các file khác truy cập được
    float baseSpeed = 0.f;
    float speedBuff = 0.f;
    float speedBuffTimer = 0.f;
    float baseSpeedOriginal = 0.f; // Thêm biến này
    float reloadSpeed = 1.0f;

private:
    float health;
    float maxHealth;
    float damage;

    // Thêm biến cho shield và speed buff
    float shield = 0.f;
    float shieldTimer = 0.f;   // <-- Thêm biến này

    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;

    sf::Vector2f offset;
    sf::RectangleShape healthBar;

public:
    Stat(std::shared_ptr<GameObject> owner, float health = 100.f, float damage = 10.f);
    void takeDamage(float amount);

    float getHealth();
    float getMaxHealth();
    float getDamage();

    // Thêm getter cho shield và speed
    float getShield() const { return shield; }
    float getSpeedBuff() const { return speedBuff; }

    // Thêm hàm xử lý shield và speed buff
    void addShield(float amount) { shield += amount; }
    void addSpeedBuff(float amount, float duration);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    // Thêm vào public
    void setHealth(float value);
    void addShield(float amount, float duration);
    float getSpeed() const;

    // Thêm hàm nâng cấp
    void upgradeBaseDamage();
    void upgradeBaseHealth();
    void upgradeReload();
    void upgradeBaseSpeed();

    // Thêm biến cấp độ nâng cấp
    int damageUpgradeLevel = 0;
    int healthUpgradeLevel = 0;
    int reloadUpgradeLevel = 0;
    int speedUpgradeLevel = 0;
};
