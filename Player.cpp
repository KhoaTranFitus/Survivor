#include "Player.h"

Player::Player()
{
	hitbox.setSize(sf::Vector2f(50.f, 50.f));
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setPosition(615.f, 335.f);
	this->tag = "player";
}

Player::~Player()
{
}
