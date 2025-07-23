#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(float x, float y);
	Bullet(sf::Vector2f position);
	virtual ~Bullet();
};