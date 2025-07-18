#pragma once
#include <SFML/Graphics.hpp>
class Scene
{
private:
	
public: 
	Scene() = default;
	virtual ~Scene() = default;
	virtual void update(float deltaTime);
	virtual void render(sf::RenderWindow& window);
};

