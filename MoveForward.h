#pragma once
#include "Component.h"
class MoveForward : public Component
{
private:
	sf::Vector2f direction;
	sf::Vector2f targetPosition;
	float speed;
public:
	MoveForward(std::shared_ptr<GameObject> owner, sf::Vector2f targetPosition,float speed = 400.f);
	void update(float deltaTime) override;
};

