#pragma once

#include "Component.h"
#include "GameObject.h"
#include <iostream>

class KeyboardMove : public Component
{
private:
	float speed;
	std::string mode;
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
public:
	KeyboardMove(std::shared_ptr<GameObject> owner, float speed, std::string mode = "wasd");

	sf::Vector2f getDirection() const;
	float getSpeed() const { return speed; }
	void setSpeed(float newSpeed) { speed = newSpeed; }
	void update(float deltaTime) override;
};

