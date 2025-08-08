#include "Bullet.h"
#include "Assets.h"
sf::Texture Bullet::playerTexture;
sf::Texture Bullet::enemyTexture;
bool Bullet::texturesLoaded = false;

void Bullet::loadTextures() {
    if (!texturesLoaded) {
        playerTexture.loadFromFile("./Assets/bullet/arrow.png");
        texturesLoaded = true;
    }
}


Bullet::Bullet(sf::Vector2f position, sf::Vector2f size, std::string tag): 
    GameObject()
{
    hitbox.setSize(size);
    hitbox.setFillColor(sf::Color::Black); // Mặc định
    hitbox.setPosition(position);
    this->tag = tag;

    loadTextures();
    if (tag == "player_bullet") {
        hitbox.setTexture(&playerTexture);
        hitbox.setFillColor(sf::Color::White); 
    } else if (tag == "enemy_bullet") {
        //hitbox.setFillColor(sf::Color::White); 

        animations = std::make_shared<Animation>(Assets::ENEMY_BULLET,4,0.1,
            sf::Vector2i(10, 10));
		animations->setScale(sf::Vector2f(2.f,2.f));
		animations->setCenter();
		animations->setPosition(position + size/2.f);
    }

}

Bullet::~Bullet()
{
}

void Bullet::update(float deltaTime)
{
    GameObject::update(deltaTime);
    this->lifeTime += deltaTime;
    if (lifeTime > 3.f)
    {
        needDeleted = true;
    }
    if (animations) {
        animations->update(deltaTime, false);
        animations->setPosition(hitbox.getPosition() + hitbox.getSize() / 2.f);
    }
}

void Bullet::setImageScale(const sf::Vector2f& scale) {
    hitbox.setScale(scale);
}

void Bullet::render(sf::RenderWindow& window)
{
    if (animations) {
        animations->render(window);
    } else if (hitbox.getTexture()) {
        window.draw(hitbox);
    } else {
        window.draw(hitbox);
    }
}