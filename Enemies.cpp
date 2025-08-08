#include "Enemies.h"
#include "GameManager.h"
#include "GameObjectFactory.h"
#include "SwitchSceneCommand.h"
#include "VictoryScene.h"
#include "Assets.h"
#include "Animation.h"
#include <random> // Thêm dòng này ở đầu file

Enemies::Enemies()
{
	hitbox.setSize(sf::Vector2f(30.f, 30.f));
	hitbox.setFillColor(sf::Color::Red);
	hitbox.setPosition(600.f, 600.f);
	this->setTag("Enemies");

	// Add run animationa+*****
}

Enemies::~Enemies()
{	
}

void Enemies::onDestroy()
{
	float x = this->getOrigin().x;
	float y = this->getOrigin().y;

	// Danh sách các powerup hợp lệ
	static const std::vector<std::string> powerUpNames = { "shield", "speed", "health_type1","health_type2"};

	// Random: 0-99, <70 là gem, >=70 là powerup
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distType(0, 99);
	int type = distType(gen);

	if (type < 80) { // 70% tạo gem
		GameManager::getInstance().getCurrentScene()->addGameObject(
			GameObjectFactory::createGem(x, y)
		);
	} else { // 30% tạo powerup ngẫu nhiên
		std::uniform_int_distribution<> distPowerUp(0, static_cast<int>(powerUpNames.size()) - 1);
		std::string selectedPowerUp = powerUpNames[distPowerUp(gen)];
		GameManager::getInstance().getCurrentScene()->addGameObject(
			GameObjectFactory::createPowerUp(selectedPowerUp, x, y)
		);
	}

	// Nếu là boss thì chuyển sang VictoryScene
	if (this->getTag() == "boss")
	{
		auto switchCommand = std::make_shared<SwitchSceneCommand>([]() {
			return std::make_shared<VictoryScene>();
		});
		switchCommand->execute();
	}
}