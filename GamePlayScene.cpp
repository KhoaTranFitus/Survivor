#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"
#include <sstream>
#include "PauseScene.h"
#include "PlayerStat.h"
#include "NoOverlapComponent.h"
#include "LoseScene.h"
#include <cmath>
#include "Shield.h"
#include "Speed.h"

sf::Font GamePlayScene::font;
bool GamePlayScene::fontLoaded = false;
GamePlayScene::GamePlayScene()
{
	//thêm background
	if (!fontLoaded) {
		fontLoaded = font.loadFromFile("arial.ttf");
	}
	clockInGame = std::make_shared<Clock>();
	gameObjects.push_back(GameObjectFactory::createBackground("./Assets/backGround/Game1.jpg"));
	//player
	auto player = GameObjectFactory::createPlayer();
	gameObjects.push_back(player);

	//add item in game play scene

	auto playPause = std::make_shared<Button>(
		"", "pause", 50, 50, sf::Vector2f(50, 50),
		std::make_shared<SwitchSceneCommand>([this]() {
			return std::make_shared<PauseScene>(shared_from_this());
			})
	);
	buttons.push_back(playPause);
}

GamePlayScene::~GamePlayScene()
{
}
float distance(sf::Vector2f a, sf::Vector2f b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return std::sqrt(dx * dx + dy * dy);
}

void GamePlayScene::spawnEnemyGeneric(
	std::function<std::shared_ptr<Enemies>()> factory,
	float& elapsed, float cooldown,
	const sf::FloatRect& spawnRect,
	const sf::FloatRect& viewRect,
	const sf::Vector2f& playerPos,
	float minDistanceToPlayer,
	float deltaTime
)
{
	elapsed += deltaTime;
	if (elapsed >= cooldown)
	{
		elapsed = 0.0f;
		float spawnX, spawnY;
		int maxTry = 10;
		bool valid = false;
		for (int tryCount = 0; tryCount < maxTry && !valid; ++tryCount) {
			spawnX = spawnRect.left + static_cast<float>(rand()) / RAND_MAX * spawnRect.width;
			spawnY = spawnRect.top + static_cast<float>(rand()) / RAND_MAX * spawnRect.height;
			if (distance(sf::Vector2f(spawnX, spawnY), playerPos) >= minDistanceToPlayer)
				valid = true;
		}
		if (!valid) {
			spawnX = viewRect.left - (spawnRect.left - viewRect.left);
			spawnY = viewRect.top - (spawnRect.top - viewRect.top);
		}
		auto enemy = factory();
		if (enemy)
		{
			enemy->addComponent(std::make_shared<NoOverlapComponent>(enemy, &gameObjects));
			enemy->getHitbox().setPosition(sf::Vector2f(spawnX, spawnY));
			gameObjects.push_back(enemy);
		}
	}
}

void GamePlayScene::update(float deltaTime)
{
	Scene::update(deltaTime);

	this->camera.update(deltaTime, GameManager::getInstance().currentPlayer->getHitbox().getPosition());
	// thời gian đến khi dừng game
	float elapsed = getElapsedTime();
	bool stopAll = (elapsed >= 120.f);

	if (clockInGame && !clockInGame->isPaused()) {
		if (stopAll) {
			clockInGame->pause();
		}
		else {
			clockInGame->update(deltaTime);
		}
	}

	sf::FloatRect viewRect = camera.getViewRect();
	float margin = 100.f;
	float minDistanceToPlayer = 100.f;
	sf::Vector2f playerPos = GameManager::getInstance().currentPlayer->getHitbox().getPosition();

	sf::FloatRect spawnRect(
		viewRect.left - margin,
		viewRect.top - margin,
		viewRect.width + 2 * margin,
		viewRect.height + 2 * margin
	);

	// Nếu chưa đến 2 phút thì vẫn spawn enemy
	if (!stopAll) {
		spawnEnemyGeneric(
			[]() { return GameObjectFactory::createDefaultEnemy(); },
			defaultEnemyElapsed, defaultEnemyCooldown,
			spawnRect, viewRect, playerPos, minDistanceToPlayer,
			deltaTime
		);

		spawnEnemyGeneric(
			[]() { return GameObjectFactory::createShooterEnemy(); },
			shooterEnemyElapsed, shooterEnemyCooldown,
			spawnRect, viewRect, playerPos, minDistanceToPlayer,
			deltaTime
		);

		spawnEnemyGeneric(
			[]() { return GameObjectFactory::createTankerEnemy(); },
			tankerEnemyElapsed, tankerEnemyCooldown,
			spawnRect, viewRect, playerPos, minDistanceToPlayer,
			deltaTime
		);

		spawnEnemyGeneric(
			[]() { return GameObjectFactory::createBurstEnemy(); },
			burstEnemyElapsed, burstEnemyCooldown,
			spawnRect, viewRect, playerPos, minDistanceToPlayer,
			deltaTime
		);
	}
	else {
		// XÓA CHỈ 1 LẦN
		if (!clearedEnemiesAndBullets) {
			clearedEnemiesAndBullets = true;
			gameObjects.erase(
				std::remove_if(gameObjects.begin(), gameObjects.end(),
					[](const std::shared_ptr<GameObject>& obj) {
						if (obj->getTag() == "enemies") return true;
						if (obj->getTag() == "bullet") return true;
						return false;
					}
				),
				gameObjects.end()
			);
		}
		// Spawn boss như cũ
		if (stopAll && !bossSpawned) {
			bossSpawned = true;
			sf::FloatRect viewRect = camera.getViewRect();
			float bossX = viewRect.left + viewRect.width / 2.f;
			float bossY = viewRect.top + viewRect.height / 2.f;
			auto boss = GameObjectFactory::createBoss();
			boss->getHitbox().setPosition(sf::Vector2f(bossX, bossY));
			gameObjects.push_back(boss);
		}
	}
	
	// Xử lý player chết: đếm ngược deadPlayerTimer và xóa player khi hết thời gian, đồng thời chuyển LoseScene
	
	//kiem tra alive player
	if (!alivePlayer() && !playerPendingDelete) {
		// Bắt đầu quá trình đếm ngược
		playerPendingDelete = true;
		deadPlayerTimer = 1.55f;  // thời gian hiển thị animation chết
		loseDelayTimer = 1.45f;   // thời gian trước khi chuyển scene
	}

	if (playerPendingDelete) {
		deadPlayerTimer -= deltaTime;
		loseDelayTimer -= deltaTime;

		if (deadPlayerTimer <= 0.f) {
			// Xóa player khỏi gameObjects
			gameObjects.erase(
				std::remove_if(gameObjects.begin(), gameObjects.end(),
					[](const std::shared_ptr<GameObject>& obj) {
						return obj->getTag() == "player";
					}
				),
				gameObjects.end()
			);
		}

		if (loseDelayTimer <= 0.f) {
			this->pauseClock();
			auto loseScene = std::make_shared<LoseScene>(shared_from_this());
			GameManager::getInstance().setScene(loseScene);
			return;
		}
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


	auto player = GameManager::getInstance().currentPlayer;
	if (fontLoaded && player) {
	    auto playerStat = player->getComponent<PlayerStat>();
	    if (playerStat) {
	        playerStat->render(window, font);
	    }
	
	   auto shield = player->getComponent<Shield>();
	    if (shield) shield->render(window);

	    auto speed = player->getComponent<Speed>();
	    if (speed) speed->render(window);

	}
	renderClock(window);
}

void GamePlayScene::renderClock(sf::RenderWindow& window, sf::Vector2f position, sf::Color color, unsigned int size)
{
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
        sf::Text text(oss.str(), font, size);
        text.setFillColor(color);
        text.setPosition(position);
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

bool GamePlayScene::alivePlayer()
{
	for (auto& obj : gameObjects)
	{
		if (obj->getTag() == "player")
		{
			auto stat = obj->getComponent<Stat>();
			if (stat) {
				if (stat->getHealth() > 0) {
					return true;
				}
				else {
					// Chỉ set state DIE nếu chưa phải DIE
					if (obj->getCurrentState() != 4) {
						obj->setState(4); // Set DIE state
						deadPlayerTimer = 1.55f; // Thời gian chờ xóa player và chuyển LoseScene
						playerPendingDelete = true;
						waitingForLose = true;
						loseDelayTimer = 1.45f; // Đồng bộ với deadPlayerTimer
					}
				}
			}
		}
	}
	return false;
}