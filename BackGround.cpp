#include "BackGround.h"

Background::Background(const std::string& imagePath)
{
    if (!texture.loadFromFile("./Assets/backGround/Game1.jpg")) {
        std::cerr << "Failed to load background image\n";
    }
    else {
        sprite.setTexture(texture);
    }
    sprite.setPosition(0, 0);
}


void Background::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::Sprite& Background::getSprite()
{
	return sprite;
}