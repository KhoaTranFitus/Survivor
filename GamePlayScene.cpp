#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"
#include <sstream>
#include "PauseScene.h"
#include "LoseScene.h"
sf::Font GamePlayScene::font;
bool GamePlayScene::fontLoaded = false;
GamePlayScene::GamePlayScene()
{
	//thêm background
	if (!fontLoaded) {
		fontLoaded = font.loadFromFile("arial.ttf");
		clockInGame = std::make_shared<Clock>();
		gameObjects.push_back(GameObjectFactory::createBackground("./Resource/backGround/Game1.jpg"));
	}
	//player
	auto player = GameObjectFactory::createPlayer();
	gameObjects.push_back(player);

	//add item in game play scene
	//gameObjects.push_back(GameObjectFactory::createPowerUp("shoot", 400, 400));
	//gameObjects.push_back(GameObjectFactory::createPowerUp("move", 600, 400));
	gameObjects.push_back(GameObjectFactory::createPowerUp("heal", 100,100));


	// buttons
	auto playBack = std::make_shared<Button>(
		"Back", 100, 600, sf::Vector2f(50, 50),
		std::make_shared<SwitchSceneCommand>([]() {
			return std::make_shared<SelectLevelScene>();
			})
	);
	buttons.push_back(playBack);

	auto playPause = std::make_shared<Button>(
		"Pause", 100, 100, sf::Vector2f(50, 50),
		std::make_shared<SwitchSceneCommand>([this]() {
			return std::make_shared<PauseScene>(shared_from_this());
			})
	);
	buttons.push_back(playPause);
}

GamePlayScene::~GamePlayScene()
{
}
bool GamePlayScene::alivePlayer()
{
	for (auto& obj : gameObjects)
	{
		if (obj->getTag() == "player")
		{
			auto stat = obj->getComponent<Stat>();
			if (stat && stat->getHealth() > 0) {
				return true;
			}
		}
	}
	return false;
}


void GamePlayScene::update(float deltaTime)
{
	Scene::update(deltaTime);

	this->camera.update(deltaTime, GameManager::getInstance().currentPlayer->getHitbox().getPosition());

	if (clockInGame && !clockInGame->isPaused()) clockInGame->update(deltaTime);


	//cho enenmy spawn ow ngoai khung camera
	enemySpawnElapsed += deltaTime;
	if (GameManager::getInstance().isKeyPressed(sf::Keyboard::Enter))
		//if (enemySpawnElapsed >= enemySpawnCooldown)
	{
		enemySpawnElapsed = 0.0f;
		//check player is exist
		sf::FloatRect viewRect = camera.getViewRect();
		float spawnX = 0.f;
		float spawnY = 0.f;
		// Chọn 1 trong 4 phía: 0 = trái, 1 = phải, 2 = trên, 3 = dưới
		int side = rand() % 4;
		float margin = 100.f; // spawn cách rìa camera khoảng 100 px

		switch (side)
		{
		case 0: // trái
			spawnX = viewRect.left - margin;
			spawnY = viewRect.top + rand() / viewRect.height;
			break;
		case 1: // phải
			spawnX = viewRect.left + viewRect.width + margin;
			spawnY = viewRect.top + rand() / viewRect.height;
			break;
		case 2: // trên
			spawnX = viewRect.left + rand() / viewRect.width;
			spawnY = viewRect.top - margin;
			break;
		case 3: // dưới
			spawnX = viewRect.left + rand() / viewRect.width;
			spawnY = viewRect.top + viewRect.height + margin;
			break;
		}
		auto enemy = GameObjectFactory::createEnemy();
		if (enemy)
		{
			enemy->getHitbox().setPosition(sf::Vector2f(spawnX, spawnY));
			gameObjects.push_back(enemy);
		}
	}
	if (!alivePlayer()) {
		GameManager::getInstance().setScene(std::make_shared<LoseScene>(shared_from_this()));
		return;
	}
}

void GamePlayScene::render(sf::RenderWindow& window)
{
	window.setView(camera.getView(window.getSize())); // Cập nhật camera theo vị trí của người chơi
	for (auto& gameObject : gameObjects) {
		gameObject->render(window);
	}
	window.setView(window.getDefaultView());
	// Render buttons
	for (const auto& button : buttons) {
		button->render(window);
	}

	// Render the clock in game play scene with form "Time: mm:ss"
	if (fontLoaded) {
		int elapsed = static_cast<int>(getElapsedTime());
		int minutes = elapsed / 60;
		int seconds = elapsed % 60;
		std::ostringstream oss;
		oss << "Time: ";
		if (minutes < 10) oss << '0';
		oss << minutes << ":";
		if (seconds < 10) oss << '0';
		oss << seconds;
		sf::Text text(oss.str(), font, 24);
		text.setFillColor(sf::Color::Green);
		text.setPosition(10, 10); // Góc trên bên trái
		window.draw(text);
	}
}

float GamePlayScene::getElapsedTime() const {
	if (clockInGame)
	{
		return clockInGame->getElapsedSeconds();
	}
	return 0.f;
}

void GamePlayScene::pauseClock() {
	if (clockInGame) clockInGame->pause();
}

void GamePlayScene::resumeClock() {
	if (clockInGame) clockInGame->resume();
}
