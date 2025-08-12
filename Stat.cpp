#include "Stat.h"
#include "GameObject.h"

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage) :
	Component(owner), health(health), maxHealth(health), damage(damage) // Gán maxHealth = health ban ??u
{
	//neu la enemy thi ko ender health bar
	if (owner->getTag() == "player")
	{
	this->healthBar.setSize(sf::Vector2f(50.f, 12.f));
	this->healthBar.setFillColor(sf::Color::Green);
	auto hitbox = this->owner->getHitbox();
	offset.x = hitbox.getPosition().x + hitbox.getSize().x / 2 - this->healthBar.getSize().x / 2;
	offset.y = hitbox.getPosition().y - this->healthBar.getSize().y - 5;
	offset = offset - hitbox.getPosition();
	}

	updateHealthBar();
}

void Stat::update(float deltaTime)
{
	auto hitbox = this->owner->getHitbox();

	this->healthBar.setPosition(hitbox.getPosition() + offset);
}

void Stat::render(sf::RenderWindow& window)
{
	window.draw(this->healthBar);
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

void Stat::setHealth(float value)
{
	health = value;
	if (health > maxHealth) health = maxHealth;
	if (health < 0) health = 0;
	updateHealthBar();
}

void Stat::setDamage(float value)
{
	damage = value;
}

void Stat::updateHealthBar()
{
	float percent = (maxHealth > 0) ? (health / maxHealth) : 0.f;
	if (percent < 0) percent = 0;
	healthBar.setSize(sf::Vector2f(50 * percent, 10));
}

