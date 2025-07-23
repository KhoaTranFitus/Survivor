#pragma once

#include "Component.h"

class Stat : public Component
{
private:
	float health;
	float maxHealth; // Thêm dòng này
	float damage;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration; // trái ngh?a v?i gia t?c, gi?ng l?c ma sát cho nó d?ng l?i

	sf::Vector2f offset;
	sf::RectangleShape healthBar;

public:
	Stat(std::shared_ptr<GameObject> owner, float health = 100.f, float damage = 10.f);
	void takeDamage(float amount);

	float getHealth();
	float getMaxHealth(); // Thêm getter
	float getDamage();

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};
