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
	gameObjects.push_back(GameObjectFactory::createPowerUp("heal", 100, 100));


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

// Hàm tính khoảng cách 2 điểm
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
	bool stopAll = (elapsed >= 5.f);

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

	auto player = GameManager::getInstance().currentPlayer;
	if (fontLoaded && player) {
	    auto playerStat = player->getComponent<PlayerStat>();
	    if (playerStat) {
	        playerStat->render(window, font);
	    }
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

