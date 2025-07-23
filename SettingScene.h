#pragma once
#include "Scene.h"
#include <algorithm>  
class SettingScene :public Scene
{
private:
	sf::RectangleShape volumeBar;
	sf::CircleShape volumeDot;
	bool isDragging = false;
	float volume = 50.f;

public:
	SettingScene();
	~SettingScene();

	void update(float deltaTime);
	void render(sf::RenderWindow& window) override;
};

