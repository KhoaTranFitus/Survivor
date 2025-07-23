#include "Button.h"


sf::Font Button::font;
Button::Button(const std::string& n_text, float x, float y, sf::Vector2f size, std::shared_ptr<ICommand> command)
{
    //text at button
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Khong load duoc font" << std::endl;
        }
        fontLoaded = true;
    }
    text.setFont(font);
    text.setString(n_text);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    // can giua nut
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(x + size.x / 2.0f, y + size.y / 2.0f);
    hitbox.setSize(size);
    hitbox.setPosition(x, y);
    hitbox.setFillColor(sf::Color::Blue);
    hitbox.setOutlineThickness(2.f);
    hitbox.setOutlineColor(sf::Color::Black);
	this->command = command;
}

Button::~Button()
{
}

void Button::update(float deltaTime)
{
    bool mouseNowDown = GameManager::getInstance().isMousePressed(sf::Mouse::Left);
    sf::Vector2f mousePos = mousePosition;
    sf::Vector2f posF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (hitbox.getGlobalBounds().contains(posF)) {
        if (!isHovered) {
            hitbox.setFillColor(sf::Color::Green);
            isHovered = true;
        }
        if (mouseNowDown && !wasMouseDown) {
            std::cout << "Button clicked: " << text.getString().toAnsiString() << std::endl;
            if (command) command->execute(); // <--- Add this check
        }
    }
    else {
        if (isHovered) {
            hitbox.setFillColor(sf::Color::Blue);
            isHovered = false;
        }
    }
    wasMouseDown = mouseNowDown;
}

void Button::render(sf::RenderWindow& window)
{
    window.draw(hitbox);
    window.draw(text);
}
