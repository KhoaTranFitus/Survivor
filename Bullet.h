#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Bullet : public GameObject
{
public:
	Bullet(sf::Vector2f position, sf::Vector2f size, std::string tag);
	virtual ~Bullet();

	void setImageScale(const sf::Vector2f& scale);
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window);
private: 
	float lifeTime = 0.f;
	std::string tag;
	static sf::Texture playerTexture;
	static sf::Texture enemyTexture;
	static bool texturesLoaded;
	void loadTextures();

	std::shared_ptr<Animation> animations;
};