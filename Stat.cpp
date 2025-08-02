#include "Stat.h"
#include "Heal.h"
#include "Speed.h"
#include "Shield.h"
#include "GameObject.h"

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage, float speed)
    : Component(owner), health(health), maxHealth(health), damage(damage), baseSpeed(speed){
}

float Stat::getHealth() const {
    return health;
}

float Stat::getMaxHealth() const {
    return maxHealth;
}

float Stat::getDamage() const {
    return damage;
}

float Stat::getBaseSpeed() const {
    return baseSpeed;
}

float Stat::getCurrentSpeed() const {
    float speed = baseSpeed;
    auto speedBuff = owner->getComponent<Speed>();
    if (speedBuff) speed += speedBuff->getBonus();
    return speed;
}

void Stat::takeDamage(float amount) {
    auto shield = owner->getComponent<Shield>();
    if (shield) {
        float remaining = amount - shield->getShield();
        owner->removeComponent<Shield>();
        if (remaining > 0) health -= remaining;
    }
    else {
        health -= amount;
    }

    if (health < 0) health = 0;
}

void Stat::heal(float amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Stat::modifySpeed(float deltaTime) {
    baseSpeed += deltaTime;
}

void Stat::modifyShield(float deltaTime) {
    shield += deltaTime;
    if (shield < 0.f) shield = 0.f;
}

void Stat::upgradeBaseDamage(float amount) {
    damage += amount;
    damageUpgradeLevel++;
}

void Stat::upgradeBaseSpeed(float amount) {
    baseSpeed += amount;
    speedUpgradeLevel++;
}

void Stat::upgradeBaseHealth() {
    float added = maxHealth * 0.2f;    // tăng 20% máu tối đa hiện tại
    maxHealth += added;
    health += added;                  // tăng cả máu hiện tại
    healthUpgradeLevel++;
}


void Stat::upgradeBaseReload(float amount) {
    reloadSpeed += amount;
    if (reloadSpeed < 0.1f) reloadSpeed = 0.1f; // tránh reload âm
    reloadUpgradeLevel++;
}


