#include "Stat.h"
#include "GameObject.h"

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage)
    : Component(owner), health(health), maxHealth(health), damage(damage), speedBuff(0.f), speedBuffTimer(0.f), shield(0.f), shieldTimer(0.f), baseSpeed(0.f), baseSpeedOriginal(0.f)
{
	this->healthBar.setSize(sf::Vector2f(50.f, 12.f));
	this->healthBar.setFillColor(sf::Color::Green);

	auto hitbox = this->owner->getHitbox();
	offset.x = hitbox.getPosition().x + hitbox.getSize().x / 2 - this->healthBar.getSize().x / 2;
	offset.y = hitbox.getPosition().y - this->healthBar.getSize().y - 5;
	offset = offset - hitbox.getPosition();

	baseSpeedOriginal = baseSpeed;
}

void Stat::addSpeedBuff(float amount, float duration) {
    speedBuff = amount;           // chỉ cộng vào speedBuff, không động vào baseSpeed
    speedBuffTimer = duration;
}

void Stat::addShield(float amount, float duration) {
    shield = amount;
    shieldTimer = duration;
}

void Stat::update(float deltaTime)
{
	auto hitbox = this->owner->getHitbox();

	this->healthBar.setPosition(hitbox.getPosition() + offset);

	// Shield timer
	if (shieldTimer > 0.f) {
		shieldTimer -= deltaTime;
		if (shieldTimer <= 0.f) {
			shield = 0.f;
			shieldTimer = 0.f;
		}
	}

	// Speed buff timer
	if (speedBuffTimer > 0.f) {
		speedBuffTimer -= deltaTime;
		if (speedBuffTimer <= 0.f) {
			speedBuff = 0.f;      // hết buff, trả lại tốc độ gốc
			speedBuffTimer = 0.f;
		}
	}
}

void Stat::render(sf::RenderWindow& window)
{
	window.draw(this->healthBar);
}

void Stat::takeDamage(float amount)
{
    // Nếu còn shield, không nhận bất kỳ sát thương nào
    if (shield > 0.f && shieldTimer > 0.f) {
        // Không trừ máu, không trừ shield
        return;
    }

    // Nếu không có shield, trừ máu như bình thường
    health -= amount;
    if (health > maxHealth) health = maxHealth;
    if (health < 0) health = 0;

    float percent = health / maxHealth;
    if (percent < 0) percent = 0;
    healthBar.setSize(sf::Vector2f(50 * percent, 10));
	
    if (health == 0) {
        owner->needDeleted = true;
    } 
}

void Stat::setHealth(float value) {
    health = std::min(value, maxHealth);
	float percent = health / maxHealth;
	if (percent < 0) percent = 0;
	healthBar.setSize(sf::Vector2f(50 * percent, 10));
}

float Stat::getHealth()
{
	return this->health;
}

float Stat::getDamage()
{
	return this->damage;
}

float Stat::getMaxHealth()
{
	return maxHealth;
}

float Stat::getSpeed() const {
    return baseSpeed + speedBuff;
}

void Stat::upgradeBaseDamage() {
    if (damageUpgradeLevel < 5) {
        damage += 5; // hoặc giá trị bạn muốn
        damageUpgradeLevel++;
    }
}
void Stat::upgradeBaseHealth() {
    if (healthUpgradeLevel < 5) {
        maxHealth += 20;
        health += 20;
        healthUpgradeLevel++;
    }
}
void Stat::upgradeReload() {
    if (reloadUpgradeLevel < 5) {
        reloadSpeed *= 0.9f; // giảm 10% thời gian reload
        reloadUpgradeLevel++;
    }
}
void Stat::upgradeBaseSpeed() {
    if (speedUpgradeLevel < 5) {
        baseSpeed += 30.f;
        speedUpgradeLevel++;
    }
}
