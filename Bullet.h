#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
private: 
	float lifeTime = 0.f;
public:
	Bullet(float x, float y);
	Bullet(sf::Vector2f position);
	Bullet(sf::Vector2f position, sf::Vector2f size); // Ensure constructor supports size
	void update(float deltaTime) override;
	virtual ~Bullet();
};