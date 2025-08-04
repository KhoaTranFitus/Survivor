#include "Bullet.h"

sf::Texture Bullet::playerTexture;
sf::Texture Bullet::enemyTexture;
bool Bullet::texturesLoaded = false;

void Bullet::loadTextures() {
    if (!texturesLoaded) {
        playerTexture.loadFromFile("./Assets/bullet/arrow.png");
        enemyTexture.loadFromFile("./Assets/bullet/bullet_enemy.png");
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
        hitbox.setFillColor(sf::Color::White); // Sửa ở đây
    } else if (tag == "bullet_enemy") {
        hitbox.setTexture(&enemyTexture);
        hitbox.setFillColor(sf::Color::White); // Sửa ở đây
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
}

void Bullet::setImageScale(const sf::Vector2f& scale) {
    hitbox.setScale(scale);
}

void Bullet::render(sf::RenderWindow& window)
{
    if (hitbox.getTexture()) {
        window.draw(hitbox); // Vẽ hình (ảnh)
    } else {
        window.draw(hitbox); // Vẽ hitbox (màu)
    }
}