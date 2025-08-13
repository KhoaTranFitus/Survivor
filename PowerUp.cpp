#include "PowerUp.h"
#include "ItemEffect.h"
#include "Shield.h"
#include "Speed.h"
#include "Heal.h"
#include "Assets.h"

PowerUp::PowerUp(): GameObject()
{
	this->getHitbox().setSize(sf::Vector2f(32, 32));
	this->getHitbox().setFillColor(sf::Color::Magenta);
	this->getHitbox().setPosition(500, 500);
}

PowerUp::~PowerUp()
{
}

std::shared_ptr<PowerUp> PowerUp::Create(const std::string& name, float x, float y)
{
    auto powerUp = std::make_shared<PowerUp>();
    powerUp->setTag("item");
    powerUp->getHitbox().setPosition(x, y);

    if (name == "shield")
    {
        powerUp->addComponent(std::make_shared<ItemEffect>(
            powerUp,
            [](std::shared_ptr<GameObject> target) {
                return std::make_shared<Shield>(target, 50.f, 5.f);
            }
        ));
        powerUp->sprite.setTexture(Assets::SHIELD);
		powerUp->sprite.setScale(1.5f, 1.5f);
    }
    else if (name == "speed")
    {
        powerUp->addComponent(std::make_shared<ItemEffect>(
            powerUp,
            [](std::shared_ptr<GameObject> target) {
                return std::make_shared<Speed>(target, 100.f, 5.f);
            }
        ));
		powerUp->sprite.setTexture(Assets::SPEED);
        powerUp->sprite.setScale(3.f, 3.f);
    }
    else if (name == "health_type1")
    {
        powerUp->addComponent(std::make_shared<ItemEffect>(
            powerUp,
            [](std::shared_ptr<GameObject> target) {
                return std::make_shared<Heal>(target, 0.1f);
            }
        ));
        //powerUp->getHitbox().setFillColor(sf::Color::Green);
        powerUp->sprite.setTexture(Assets::HEALTH_TYPE1);
        powerUp->sprite.setScale(1.25f, 1.25f);

    }
    else if (name == "health_type2")
    {
        powerUp->addComponent(std::make_shared<ItemEffect>(
            powerUp,
            [](std::shared_ptr<GameObject> target) {
                return std::make_shared<Heal>(target, 0.2f);
            }
        ));
        //powerUp->getHitbox().setFillColor(sf::Color:: Black);
        powerUp->sprite.setTexture(Assets::HEALTH_TYPE2);
    powerUp->sprite.setScale(1.25f, 1.25f);
    }
    return powerUp;
}

void PowerUp::render(sf::RenderWindow& window)
{
    if (sprite.getTexture() != nullptr) {
        sprite.setPosition(getHitbox().getPosition());
        window.draw(sprite);
    } else {
        window.draw(getHitbox());
	}
 
}