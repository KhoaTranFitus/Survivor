#include "Enemies.h"

Enemies::Enemies()
{
	hitbox.setSize(sf::Vector2f(50.f, 50.f));
	hitbox.setFillColor(sf::Color::Red);
	hitbox.setPosition(600.f, 600.f);
	this->getTag() = "Enemy";
}

Enemies::~Enemies()
{
}