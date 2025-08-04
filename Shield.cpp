#include "Shield.h"
#include "Stat.h"
#include "GameObject.h"

Shield::Shield(std::shared_ptr<GameObject> owner, float amount, float duration)
    : Component(owner), shieldAmount(amount), duration(duration), timer(0.f) {
}

void Shield::onCollisionEnter(std::shared_ptr<GameObject> other) {
    // Do nothing: shield blocks all damage while active
}

void Shield::update(float deltaTime) {
    timer += deltaTime;
    if (timer >= duration) {
        owner->removeComponent<Shield>();
    }
}

void Shield::render(sf::RenderWindow& window) {
    float barWidth = 120.f;
    float barHeight = 16.f;
    float margin = 20.f;
    float windowWidth = window.getSize().x;
    float x = windowWidth - barWidth - margin;
    float y = margin;

    float percent = 1.f - (timer / duration);

    // Bar background
    sf::RectangleShape bg(sf::Vector2f(barWidth, barHeight));
    bg.setFillColor(sf::Color(50, 50, 100, 180));
    bg.setPosition(x, y);
    window.draw(bg);

    // Bar fill
    sf::RectangleShape bar(sf::Vector2f(barWidth * percent, barHeight));
    bar.setFillColor(sf::Color::Blue);
    bar.setPosition(x, y);
    window.draw(bar);

    // Small square button
    float squareSize = barHeight;
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::Blue);
    square.setOutlineColor(sf::Color::White);
    square.setOutlineThickness(2.f);
    square.setPosition(x - 30.f, y); // 8px padding from bar
    window.draw(square);

    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        fontLoaded = font.loadFromFile("arial.ttf");
    }
}