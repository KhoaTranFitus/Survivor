#include "Bullet.h"

Bullet::Bullet(float x, float y) :
	GameObject()
{
	hitbox.setSize(sf::Vector2f(10.f, 10.f));
	hitbox.setFillColor(sf::Color::Black);
	hitbox.setPosition(x, y);
}

Bullet::Bullet(sf::Vector2f position):
	GameObject()
{
	hitbox.setSize(sf::Vector2f(10.f, 10.f));
	hitbox.setFillColor(sf::Color::Black);
	hitbox.setPosition(position);
}

Bullet::~Bullet()
{
}