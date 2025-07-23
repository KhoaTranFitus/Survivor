#include "PowerUp.h"

PowerUp::PowerUp(): GameObject()
{
	this->getHitbox().setSize(sf::Vector2f(32, 32));
	this->getHitbox().setFillColor(sf::Color::Magenta);
	this->getHitbox().setPosition(500, 500);
}

PowerUp::~PowerUp()
{
}
