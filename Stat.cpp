#include "Stat.h"
#include "GameObject.h"

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage) :
	Component(owner), health(health), maxHealth(health), damage(damage) // G�n maxHealth = health ban ??u
{
	this->healthBar.setSize(sf::Vector2f(50.f, 12.f));
	this->healthBar.setFillColor(sf::Color::Green);

	auto hitbox = this->owner->getHitbox();
	offset.x = hitbox.getPosition().x + hitbox.getSize().x / 2 - this->healthBar.getSize().x / 2;
	offset.y = hitbox.getPosition().y - this->healthBar.getSize().y - 5;
	offset = offset - hitbox.getPosition();
}

//void Stat::takeDamage(float amount)
//{
//	health = std::max(health - amount, 0.f);
//
//	if (health == 0) std::cout << "Died\n";
//	else std::cout << "Health remain: " << health << std::endl;
//
//	//update health bar size
//	this->healthBar.setSize(sf::Vector2f(100 * (health / 100), 20));
//}

void Stat::update(float deltaTime)
{
	auto hitbox = this->owner->getHitbox();

	this->healthBar.setPosition(hitbox.getPosition() + offset);
}

void Stat::render(sf::RenderWindow& window)
{
	window.draw(this->healthBar);
}

void Stat::takeDamage(float amount)
{
	health -= amount;
	if (health > maxHealth) health = maxHealth; // Kh�ng v??t qu� max  
	if (health < 0) health = 0;

	float percent = health / maxHealth;
	if (percent < 0) percent = 0;
	healthBar.setSize(sf::Vector2f(50 * percent, 10));
	std::cout << "Health remain: " << health << std::endl;

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
