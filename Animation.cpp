#include "Animation.h"
#include <iostream>	
Animation::Animation(const sf::Texture& texture, int totalFrames, float frameDuration, sf::Vector2i frameSize):
	currentFrame(0,0,frameSize.x,frameSize.y), frameIndex(0),
	totalFrames(totalFrames), frameDuration(frameDuration), frameTimer(0.0f), frameSize(frameSize)
{
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(currentFrame);
}

Animation::~Animation()
{
}
const sf::Vector2f Animation::getSize() const
{
	return sf::Vector2f(frameSize);
}

void Animation::setRotation(float angle)
{
	this->sprite.setRotation(angle);
}

void Animation::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

void Animation::setOrigin(sf::Vector2f origin)
{
	this->sprite.setOrigin(origin);
}

void Animation::setScale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}

void Animation::setSize(sf::Vector2f size)
{
	this->sprite.setScale(size.x / frameSize.x, size.y / frameSize.y);
}

//Đặt độ trong suốt
void Animation::setTransparency(int alpha)
{
	sf::Color color = this->sprite.getColor();
	color.a = alpha;
	this->sprite.setColor(color);
}

void Animation::setCenter()
{
	this->sprite.setOrigin(frameSize.x / 2.0f, frameSize.y / 2.0f);	
}


void Animation::update(float deltaTime, bool flipped)
{
	this->frameTimer = std::max(0.f, this->frameTimer - deltaTime);

	this->flipTimer += deltaTime;
	if (this->frameTimer <= 0.f)
	{
		this->frameTimer = this->frameDuration;
		this->frameIndex = (this->frameIndex + 1) % this->totalFrames;
	}

	int width = frameSize.x;
	int height = frameSize.y;
	int left = frameIndex * width;
	int top = 0;

	if (flipped)
	{
		// Bắt đầu từ cạnh phải frame hiện tại và vẽ ngược lại
		left += width; // cần cộng thêm width khi lật
		width = -width;
	}

	this->currentFrame = sf::IntRect(left, top, width, height);
	this->sprite.setTextureRect(this->currentFrame);
}

void Animation::render(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}