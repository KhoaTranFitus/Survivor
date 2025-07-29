#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
private: 
	float lifeTime = 0.f;
public:
	Bullet(float x, float y);
	Bullet(sf::Vector2f position);
	void update(float deltaTime) override;
	virtual ~Bullet();
};