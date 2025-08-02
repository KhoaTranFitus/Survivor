#include "BurstEnemy.h"

BurstEnemy::BurstEnemy(){
	hitbox.setSize(sf::Vector2f(30.f, 30.f));
	hitbox.setFillColor(sf::Color::Blue);
	hitbox.setPosition(600.f, 600.f);
}
