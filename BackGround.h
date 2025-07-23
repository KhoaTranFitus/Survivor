// Background.h
#pragma once
#include "GameObject.h"

class Background : public GameObject {
private:
    sf::Sprite sprite;
    sf::Texture texture;
public:
    Background(const std::string& imagePath);
	~Background() override = default;
    void update(float) override {}

    void render(sf::RenderWindow& window) override;

    sf::Sprite& getSprite();

    sf::FloatRect getGlobalBounds(){
        return sprite.getGlobalBounds();
    }
};
