#pragma once

#include "Scene.h"


class SelectLevelScene :public Scene
{
private:
	sf::Text title;
public: 
	SelectLevelScene();
	~SelectLevelScene();

	void render(sf::RenderWindow& window) override ; 
};

