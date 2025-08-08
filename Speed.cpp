#include "Speed.h"
#include "KeyboardMove.h"

Speed::Speed(std::shared_ptr<GameObject> owner, float multiplier, float duration)
    : Component(owner), multiplier(multiplier), duration(duration), timer(0.f)
{
    auto move = owner->getComponent<KeyboardMove>();
    if (move) {
        originalSpeed = move->getSpeed();
        move->setSpeed(originalSpeed + multiplier);
    }
}

void Speed::update(float deltaTime)
{
    timer += deltaTime;
    if (timer >= duration) {
        auto move = owner->getComponent<KeyboardMove>();
        if (move) {
            move->setSpeed(originalSpeed); // Restore original speed
        }
        owner->removeComponent<Speed>();
    }
}

void Speed::render(sf::RenderWindow& window)
{
    float barWidth = 120.f;
    float barHeight = 16.f;
    float margin = 20.f;
    float windowWidth = window.getSize().x;
    float x = windowWidth - barWidth - margin;
    float y = margin + barHeight + 10.f;

    float percent = 1.f - (timer / duration);

    // Bar background
    sf::RectangleShape bg(sf::Vector2f(barWidth, barHeight));
    bg.setFillColor(sf::Color(100, 100, 50, 180));
    bg.setPosition(x, y);
    window.draw(bg);

    // Bar fill
    sf::RectangleShape bar(sf::Vector2f(barWidth * percent, barHeight));
    bar.setFillColor(sf::Color::Yellow);
    bar.setPosition(x, y);
    window.draw(bar);

    // Small square button
    float squareSize = barHeight;
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color::Yellow);
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
