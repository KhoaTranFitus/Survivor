#pragma once

#include "Component.h"
#include <memory>

class FollowTarget : public Component
{
private:
	std::shared_ptr<GameObject> target;
	sf::Vector2f lastDirection;
	float speed;
public:
	FollowTarget(std::shared_ptr<GameObject> owner, 
		std::shared_ptr<GameObject> target, float speed = 400.f);
	virtual ~FollowTarget();

	void setTarget(std::shared_ptr<GameObject> newTarget);

	void update(float deltaTime) override;
};