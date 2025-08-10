#pragma once

#include <iostream>
#include "Scene.h"
#include "Button.h"
class VictoryScene : public Scene
{
private:
	static sf::Font font;
	static bool fontLoaded;
	sf::Text title;
public:
	VictoryScene();
	~VictoryScene();

	void render(sf::RenderWindow& window) override;

};
