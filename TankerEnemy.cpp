#include "TankerEnemy.h"

TankerEnemy::TankerEnemy(){
	hitbox.setSize(sf::Vector2f(70.f, 70.f));
	hitbox.setFillColor(sf::Color::Black);
	hitbox.setPosition(600.f, 600.f);
}
