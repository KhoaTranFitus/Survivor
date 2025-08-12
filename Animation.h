#pragma once
#include "SFML/Graphics.hpp"
class Animation
{
private:
	sf::Sprite sprite;
	sf::IntRect currentFrame;

	int frameIndex;
	int totalFrames;
	float frameDuration; // Duration for each frame in seconds
	float frameTimer; // Timer to track the elapsed time for the current frame

	float flipTimer  = 0.0f; // Timer to track the elapsed time for flipping
	float flipInterval = 0.1f; // Interval for flipping the sprite	
	sf::Vector2i frameSize; // Size of each frame in pixels
public:
	Animation(const sf::Texture& texture, int totalFrames, float frameDuration, sf::Vector2i frameSize);
	virtual ~Animation();

	const sf::Vector2f getSize() const;

	void setRotation(float angle);
	void setPosition(sf::Vector2f position);
	void setOrigin(sf::Vector2f origin);
	void setScale(sf::Vector2f scale);
	void setSize(sf::Vector2f size);
	void setTransparency(int alpha);
	void setCenter();

	sf::Vector2i getFrameSize() const;

	void update(float deltaTime, bool flipped);
	void render(sf::RenderWindow& window);

};

