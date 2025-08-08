#pragma once
#include "GameObject.h"

class Gem : public GameObject {
private:
	std::shared_ptr<Animation>animation;
	std::string tag;

public:

	Gem(sf::Vector2f position, const std::string tag );
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
};
