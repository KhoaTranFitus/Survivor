#include "Enemies.h"
#include "GameManager.h"
#include "GameObjectFactory.h"
#include "SwitchSceneCommand.h"
#include "VictoryScene.h"
#include "Assets.h"
#include "Animation.h"

Enemies::Enemies()
{
	hitbox.setSize(sf::Vector2f(28.f, 30.f));
	hitbox.setFillColor(sf::Color::Red);
	hitbox.setPosition(600.f, 600.f);
	this->setTag("Enemies");

	// Add run animation
}

Enemies::~Enemies()
{	
}

void Enemies::onDestroy()
{
	//GameManager::getInstance().getCurrentScene()->addGameObject(GameObjectFactory::createPowerUp("shoot", this->getOrigin().x, this->getOrigin().y));
	// Thêm gem khi enemy chết
	GameManager::getInstance().getCurrentScene()->addGameObject(
		GameObjectFactory::createGem(this->getOrigin().x, this->getOrigin().y)
	);

	// Nếu là boss thì chuyển sang VictoryScene
	if (this->getTag() == "boss")
	{
		auto switchCommand = std::make_shared<SwitchSceneCommand>([]() {
			return std::make_shared<VictoryScene>();
			});
		switchCommand->execute(); // Execute the command to switch scenes
	}

	// ví dụ về tạo một cái powerup khi enemy bi tiêu diệt

	//thì cái này là nó sẽ tạo ra 1 cái cục có thể cung cấp khả năng bắn cho đối tượng nhặt đc nó
	//mình có thể đánh dấu xóa nó rồi cho gem vô đây cũng oke nè
}