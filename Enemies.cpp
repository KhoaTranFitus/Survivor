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
    int randValue = rand() % 100;
    float x = this->getOrigin().x;
    float y = this->getOrigin().y;

    std::shared_ptr<GameObject> buff = nullptr;

    if (randValue < 30) { // 30% rớt heal
        buff = GameObjectFactory::createPowerUp("heal", x, y);
    } else if (randValue < 60) { // 30% rớt shield
        buff = GameObjectFactory::createPowerUp("shield", x, y);
    } else if (randValue < 80) { // 20% rớt speed
        buff = GameObjectFactory::createPowerUp("speed", x, y);
    } else if (randValue < 100) { // 20% rớt shoot
        buff = GameObjectFactory::createPowerUp("shoot", x, y);
    }

    if (buff) {
        GameManager::getInstance().getCurrentScene()->addGameObject(buff);
    }
}