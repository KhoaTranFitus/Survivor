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
#include <random>
#include "MusicManager.h"
#include "VictoryScene.h"
sf::Font GamePlayScene::font;
bool GamePlayScene::fontLoaded = false;
GamePlayScene::GamePlayScene()
{
	//thêm background
	MusicManager::getInstance().stop();
	MusicManager::getInstance().play("./Assets/music/gameplay.ogg", true);
	if (!fontLoaded) {
		fontLoaded = font.loadFromFile("PixelOperator8-Bold.ttf");
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

static std::random_device rd;
static std::mt19937 gen(rd());

void GamePlayScene::spawnEnemyGeneric(
	std::function<std::shared_ptr<Enemies>()> factory,
	float& elapsed, float cooldown,
	const sf::FloatRect& spawnRect,
	const sf::FloatRect& viewRect,
	const sf::Vector2f& playerPos,
	float minDistanceToPlayer,
	float deltaTime
) {
	elapsed += deltaTime;
	if (elapsed >= cooldown)
	{
		elapsed = 0.0f;
		std::uniform_real_distribution<float> distX(spawnRect.left, spawnRect.left + spawnRect.width);
		std::uniform_real_distribution<float> distY(spawnRect.top, spawnRect.top + spawnRect.height);
		float spawnX = 0.0f, spawnY = 0.0f;
		bool valid = false;
		constexpr int maxTry = 10;
		for (int tryCount = 0; tryCount < maxTry && !valid; ++tryCount) {
			spawnX = distX(gen);
			spawnY = distY(gen);
			if (distance(sf::Vector2f(spawnX, spawnY), playerPos) >= minDistanceToPlayer)
				valid = true;
		}
		if (!valid) {
			// Fallback: spawn at a random edge of spawnRect
			std::uniform_int_distribution<int> edgeDist(0, 3);
			int edge = edgeDist(gen);
			switch (edge) {
				case 0: spawnX = distX(gen); spawnY = spawnRect.top; break;
				case 1: spawnX = distX(gen); spawnY = spawnRect.top + spawnRect.height; break;
				case 2: spawnX = spawnRect.left; spawnY = distY(gen); break;
				case 3: spawnX = spawnRect.left + spawnRect.width; spawnY = distY(gen); break;
			}
		}
		auto enemy = factory();
		if (enemy)
		{
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
	bool stopAll = (elapsed >= 10.f);

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

	// Cứ mỗi 30 giây tăng thêm 1 enemy, tối đa 5 enemy/lần spawn
	int spawnCount = std::min(1 + static_cast<int>(elapsed / 45.f), 4);

	// Nếu chưa đến 2 phút thì vẫn spawn enemy
	if (!stopAll) {
		for (int i = 0; i < spawnCount; ++i) {

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

			spawnEnemyGeneric(
				[]() { return GameObjectFactory::createDashEnemy(); },
				dashEnemyElapsed, dashEnemyCooldown,
				spawnRect, viewRect, playerPos, minDistanceToPlayer,
				deltaTime
			);
		}
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

	for (auto& obj : gameObjects) {
		if (obj->getTag() == "boss") {
			auto stat = obj->getComponent<Stat>();
			if (stat && stat->getHealth() <= 0 && !bossPendingDelete) {
				obj->setState(2); // DIE state for boss
				bossDeathTimer = 2.6f; // Time for DIE animation
				bossPendingDelete = true;
			}
		}
	}

	if (bossPendingDelete) {
		bossDeathTimer -= deltaTime;
		if (bossDeathTimer <= 0.f) {
			// Remove boss from gameObjects
			gameObjects.erase(
				std::remove_if(gameObjects.begin(), gameObjects.end(),
					[](const std::shared_ptr<GameObject>& obj) {
						return obj->getTag() == "boss";
					}
				),
				gameObjects.end()
			);
			// Switch to VictoryScene
			auto victoryScene = std::make_shared<VictoryScene>();
			GameManager::getInstance().setScene(victoryScene);
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
	/*renderBossHP(window);*/

	renderClock(window, {10,10},sf::Color(10, 20, 15), 20);
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