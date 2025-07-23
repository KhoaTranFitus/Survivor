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

public:
    Button(const std::string& n_text, float x, float y, sf::Vector2f size, std::shared_ptr<ICommand> command);
    ~Button();
    void update(float deltaTime);
    void render(sf::RenderWindow& window) ;
};

