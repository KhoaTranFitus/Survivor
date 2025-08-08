#pragma once
#include "Scene.h"
#include <algorithm>  
class SettingScene :public Scene
{
private:
	sf::RectangleShape volumeBar;
	sf::CircleShape volumeDot;
	float volume = 50.f;

	sf::RectangleShape sfxBar;
	sf::CircleShape sfxDot;
	float sfxVolume = 50.f;
	
	bool isDragging = false;
	bool isDraggingSFX = false;


public:
	SettingScene();
	~SettingScene();

	void update(float deltaTime);
	void render(sf::RenderWindow& window) override;
};

