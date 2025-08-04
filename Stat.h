#pragma once

#include "Component.h"

class Stat : public Component
{
private:
	float health;
	float maxHealth;
	float damage;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;

	sf::Vector2f offset;
	sf::RectangleShape healthBar;

	void updateHealthBar();

public:
	Stat(std::shared_ptr<GameObject> owner, float health = 100.f, float damage = 10.f);

	float getHealth();
	float getMaxHealth();
	float getDamage();

	void setHealth(float value);
	void setDamage(float value);
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};
