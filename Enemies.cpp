#include "Enemies.h"
#include "GameManager.h"
#include "GameObjectFactory.h"

Enemies::Enemies()
{
	hitbox.setSize(sf::Vector2f(50.f, 50.f));
	hitbox.setFillColor(sf::Color::Red);
	hitbox.setPosition(600.f, 600.f);
}

Enemies::~Enemies()
{	
}

void Enemies::onDestroy()
{
	GameManager::getInstance().getCurrentScene()->addGameObject(GameObjectFactory::createPowerUp("shoot", this->getOrigin().x, this->getOrigin().y));
}