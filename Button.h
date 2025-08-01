#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Config.h"
#include "ICommand.h"

class Button
{
private:
    bool isHovered = false;
    bool wasMouseDown = false;

    sf::RectangleShape hitbox;

    sf::Text text;
    static sf::Font font;
    std::shared_ptr<ICommand> command;

    sf::Texture textureNormal;
    sf::Texture textureHover;
    sf::Sprite sprite;

	std::string tag; // type 1 is bigger button, type 2 is smaller button
public:
    Button(const std::string& n_text, std::string tag, float x, float y, sf::Vector2f size,
        std::shared_ptr<ICommand> command);
    ~Button();
    void update(float deltaTime);
    void render(sf::RenderWindow& window) ;

    void setTag(const std::string& n_tag) { tag = n_tag; }
    std::string getTag() const { return tag; }
};

