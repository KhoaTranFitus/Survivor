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

	float bulletCooldown = 0.75f; // bắn mỗi 0.5 giây
	float bulletElapsed = 0.f;// thời gian đã trôi qua từ lần spawn trước

	float defaultEnemyCooldown = 3.0f;
	float defaultEnemyElapsed = 0.0f;
	float shooterEnemyCooldown = 15.0f;
	float shooterEnemyElapsed = 0.0f;
	float tankerEnemyCooldown = 10.0f; 
	float tankerEnemyElapsed = 0.0f;
	float burstEnemyCooldown = 30.0f; 
	float burstEnemyElapsed = 0.0f;
    float dashEnemyCooldown = 12.0f;
	float dashEnemyElapsed = 0.0f;
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

	void renderClock(sf::RenderWindow& window, sf::Vector2f position = { 10, 10 },
		sf::Color color = sf::Color::Green, unsigned int size = 24);	
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