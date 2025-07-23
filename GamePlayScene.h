#pragma once
#include<iostream>
#include "Scene.h"
#include "Clock.h"
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
public:
	GamePlayScene();
	~GamePlayScene();


	float getElapsedTime() const; // Thêm hàm lấy thời gian đã chơi
	void pauseClock();   // Thêm
	void resumeClock();  // Thêm

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

};