#include "Button.h"


sf::Font Button::font;
Button::Button(const std::string& n_text, std::string tag, float x, float y, sf::Vector2f size, std::shared_ptr<ICommand> command)
{
    //text at button
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.loadFromFile("PixelOperator8.ttf")) {
            std::cout << "Khong load duoc font" << std::endl;
        }
        fontLoaded = true;
    }
	this->tag = tag;
    if (tag == "type1")
    {
    if (!textureNormal.loadFromFile("./Assets/button/button.png"))
        std::cerr << "Error loading normal button texture\n";
    if (!textureHover.loadFromFile("./Assets/button/button_hover.png"))
        std::cerr << "Error loading hover button texture\n";
    }
    else if (tag == "type2")
    {
        if (!textureNormal.loadFromFile("./Assets/button/button2.png"))
            std::cerr << "Error loading normal button texture\n";
        if (!textureHover.loadFromFile("./Assets/button/button2_hover.png"))
            std::cerr << "Error loading hover button texture\n";
    }
    else if(tag == "pause")
    {
        if (!textureNormal.loadFromFile("./Assets/button/pause_.png"))
            std::cerr << "Error loading normal button texture\n";
        if (!textureHover.loadFromFile("./Assets/button/pause_hover.png"))
            std::cerr << "Error loading hover button texture\n";
    }



    sprite.setTexture(textureNormal);
    sprite.setPosition(x - 20.f, y);

    text.setFont(font);
    text.setString(n_text);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color(107, 85, 74));
    // can giua nut
    sf::FloatRect textRect = text.getLocalBounds();

    if (tag == "skill") {
        text.setPosition(x + 100.f, y + size.y / 2.f + 120.f); // lệch xuống 120px
        text.setCharacterSize(20);
    }
    else {
    text.setOrigin(textRect.left + textRect.width / 2.f,
        textRect.top + textRect.height / 2.f);
        text.setPosition(x + size.x / 2.f, y + size.y / 2.f);
    }

    hitbox.setSize(size);
    hitbox.setPosition(x, y);
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
			sprite.setTexture(textureHover,true);
            sprite.setPosition(hitbox.getPosition().x - 20.f, hitbox.getPosition().y);
            isHovered = true;
        }
        if (mouseNowDown && !wasMouseDown) {
            std::cout << "Button clicked: " << text.getString().toAnsiString() << std::endl;
            if (command) command->execute(); // <--- Add this check
        }
    }
    else {
        if (isHovered) {
			sprite.setTexture(textureNormal,true);
            sprite.setPosition(hitbox.getPosition().x - 20.f, hitbox.getPosition().y);

            isHovered = false;
        }
    }
    if(this->tag == "pause")
    {
		sprite.setPosition(hitbox.getPosition().x, hitbox.getPosition().y);
	}
    wasMouseDown = mouseNowDown;
}

void Button::render(sf::RenderWindow& window)
{
	window.draw(sprite);
    //window.draw(hitbox);
    window.draw(text);
}

sf::Text Button::getText()
{
	return text;
}

void Button::setCustomTexture(const std::string& normalPath, const std::string& hoverPath)
{
    if (!textureNormal.loadFromFile(normalPath)) {
        std::cerr << "Failed to load custom normal texture: " << normalPath << std::endl;
    }
    if (!textureHover.loadFromFile(hoverPath)) {
        std::cerr << "Failed to load custom hover texture: " << hoverPath << std::endl;
    }
    sprite.setTexture(textureNormal, true);
}
