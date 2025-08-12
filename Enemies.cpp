#include "Enemies.h"
#include "GameManager.h"
#include "GameObjectFactory.h"
#include "SwitchSceneCommand.h"
#include "VictoryScene.h"
#include "Assets.h"
#include "Animation.h"
#include <random> // Thêm dòng này ở đầu file
#include "DashComponent.h"
#include "BossShoot.h"

Enemies::Enemies()
{
	hitbox.setSize(sf::Vector2f(30.f, 30.f));
	hitbox.setFillColor(sf::Color::Red);
	hitbox.setPosition(600.f, 600.f);
	this->setTag("Enemies");
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

	// Nếu là boss thì chuyển sang VictoryScene sau khi set DIE state
	//if (this->getTag() == "boss")
	//{
	//	this->setState(2); // Set DIE state for animation

	//	// Delay scene switch to allow animation to play
	//	sf::Clock* dieClock = new sf::Clock();
	//	auto self = shared_from_this();
	//	GameManager::getInstance().getCurrentScene()->addGameObject(self); // Ensure boss is still in scene

	//	// Lambda to check and switch scene after delay (e.g., 1.5s)
	//	auto switchAfterDie = [dieClock, self]() mutable {
	//		if (dieClock->getElapsedTime().asSeconds() >= 1.5f) {
	//			auto switchCommand = std::make_shared<SwitchSceneCommand>([]() {
	//				return std::make_shared<VictoryScene>();
	//			});
	//			switchCommand->execute();
	//			delete dieClock;
	//		}
	//	};
		// Register this lambda to be called in your scene's update loop (implement as needed)
		// Example: GameManager::getInstance().getCurrentScene()->addDelayedAction(switchAfterDie);
		// You need to implement addDelayedAction or similar mechanism in your scene.
	//}
}