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


Bullet::Bullet(sf::Vector2f position, sf::Vector2f size, std::string tag) :
	GameObject()
{
	hitbox.setSize(size);
	hitbox.setFillColor(sf::Color::Black); // Mặc định
	hitbox.setPosition(position);
	this->tag = tag;

	loadTextures();
	if (tag == "player_bullet") {
		hitbox.setTexture(&playerTexture);
	}
	else if (tag == "enemy_bullet") {
		sf::Vector2i frameSize(10, 10);
		animations = std::make_shared<Animation>(Assets::ENEMY_BULLET, 4, 0.1, frameSize);
		// Set a distinct scale for enemy bullets
		animations->setScale(sf::Vector2f(2.5f, 2.5f)); // Enemy bullet scale
		animations->setCenter();
		animations->setPosition(position + size / 2.f);
	}
	else if (tag == "boss_bullet")
	{
		sf::Vector2i frameSize(19, 19);
		animations = std::make_shared<Animation>(Assets::BOSS_BULLET, 4, 0.1, frameSize);
		animations->setScale(sf::Vector2f(3.f,3.f)); // Boss bullet scale
		animations->setCenter();
		animations->setPosition(position + size / 2.f);
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
		// Đảm bảo luôn đặt position là tâm hitbox (kể cả khi hitbox bị scale)
		animations->setPosition(hitbox.getPosition() );
		animations->setCenter();
		animations->setRotation(hitbox.getRotation());
	}
}

void Bullet::setImageScale(const sf::Vector2f& scale) {
	hitbox.setScale(scale);
}

void Bullet::render(sf::RenderWindow& window)
{
	if (animations) {
		animations->render(window);
	}
	 else window.draw(hitbox); // Vẽ hitbox để kiểm tra
}