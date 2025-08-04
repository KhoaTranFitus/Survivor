#pragma once

#include "Component.h"

class Stat : public Component
{
private:
	float health;
	float maxHealth; // Th�m d�ng n�y
	float damage;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration; // tr�i ngh?a v?i gia t?c, gi?ng l?c ma s�t cho n� d?ng l?i

	sf::Vector2f offset;
	sf::RectangleShape healthBar;

	void updateHealthBar();

public:
	Stat(std::shared_ptr<GameObject> owner, float health = 100.f, float damage = 10.f);

	float getHealth();
	float getMaxHealth(); // Th�m getter
	float getDamage();

	void setHealth(float health);

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};
