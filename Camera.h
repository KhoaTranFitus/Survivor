#pragma once

#include "Config.h"
#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f size;

public:
	Camera();
	virtual ~Camera();

	const sf::View getView(sf::Vector2u windowSize);
	const sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	void move(sf::Vector2f velocity);
	sf::Vector2f getSize();

	sf::FloatRect getViewRect() const;

	void update(float deltaTime, sf::Vector2f playerPosition);
};