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
	// Thêm gem khi enemy chết
	GameManager::getInstance().getCurrentScene()->addGameObject(
		GameObjectFactory::createGem(this->getOrigin().x, this->getOrigin().y)
	);

	// ví dụ về tạo một cái powerup khi enemy bi tiêu diệt

	//thì cái này là nó sẽ tạo ra 1 cái cục có thể cung cấp khả năng bắn cho đối tượng nhặt đc nó
	GameManager::getInstance().getCurrentScene()->addGameObject(GameObjectFactory::createPowerUp("shoot",
		this->getOrigin().x, this->getOrigin().y));

	//mình có thể đánh dấu xóa nó rồi cho gem vô đây cũng oke nè
}