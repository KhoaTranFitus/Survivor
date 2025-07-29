#pragma once
#include "Scene.h"
#include "GamePlayScene.h"

class LoseScene :public Scene
{
private:
	std::shared_ptr<GamePlayScene> gamePlayScene;
	std::string timeString; // luu lai thoi gian choi
public:
	LoseScene(std::shared_ptr<GamePlayScene> gamePlayScene);
	~LoseScene();
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
};

