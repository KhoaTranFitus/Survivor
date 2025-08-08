#pragma once

#include <iostream>
#include "Scene.h"
#include "Button.h"
class MenuScene: public Scene
{
private:
	static sf::Font font;
	static bool fontLoaded;
	sf::Text title;
public:
	MenuScene();
	~MenuScene();
	
	void render(sf::RenderWindow& window) override ;

};

