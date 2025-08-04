#pragma once
#include<iostream>
#include "Scene.h"
#include "Clock.h"
#include <functional> // Đảm bảo include để dùng std::function

class GamePlayScene : public Scene, public std::enable_shared_from_this<GamePlayScene>
{
private:
	static sf::Font font;
	static bool fontLoaded;
	std::shared_ptr<Clock> clockInGame;

	float enemySpawnCooldown = 3.0f;     // mỗi 3 giây spawn 1 enemy
	float enemySpawnElapsed = 0.0f;

	float bulletCooldown = 0.75f; // bắn mỗi 0.5 giây
	float bulletElapsed = 0.f;// thời gian đã trôi qua từ lần spawn trước

	float defaultEnemyCooldown = 2.0f;
	float defaultEnemyElapsed = 0.0f;
	float shooterEnemyCooldown = 5.0f;
	float shooterEnemyElapsed = 0.0f;
	bool bossSpawned = false;

	// Thêm biến này để chỉ xóa enemy và bullet 1 lần sau 2 phút
	bool clearedEnemiesAndBullets = false;

    float loseDelayTimer = 2.f; // Thời gian chờ trước khi chuyển sang LoseScene sau khi player chết
    bool waitingForLose = false;

    float deadPlayerTimer = 0.f; // Thời gian chờ xóa player và chuyển LoseScene
    bool playerPendingDelete = false; // Đánh dấu player đã chết và đang chờ xóa

public:
	GamePlayScene();
	~GamePlayScene();


	float getElapsedTime() const; // Thêm hàm lấy thời gian đã chơi
	void pauseClock();   // Thêm
	void resumeClock();  // Thêm

	bool alivePlayer();
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

private:
	// Hàm spawn enemy generic
	void spawnEnemyGeneric(
		std::function<std::shared_ptr<Enemies>()> factory,
		float& elapsed, float cooldown,
		const sf::FloatRect& spawnRect,
		const sf::FloatRect& viewRect,
		const sf::Vector2f& playerPos,
		float minDistanceToPlayer,
		float deltaTime // cần truyền deltaTime vào
	);
};