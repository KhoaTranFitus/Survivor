#include "Speed.h"
#include "KeyboardMove.h"
#include "Assets.h"
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
    // Increase bar size
    float barWidth = 180.f;   // was 120.f
    float barHeight = 28.f;   // was 16.f
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

    // Square background
    float squareSize = barHeight;
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
    square.setFillColor(sf::Color(200, 200, 50, 80));
    square.setOutlineColor(sf::Color::White);
    square.setOutlineThickness(2.f);
    square.setPosition(x - 38.f, y); // adjust for larger barHeight
    //window.draw(square);

    // Draw asset image inside square, larger and centered
    sf::Sprite iconSprite;
    iconSprite.setTexture(Assets::SPEED_ITEM);
    sf::Vector2u texSize = Assets::SPEED_ITEM.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        // Make icon larger (e.g. 1.8x the square size)
        float iconTargetSize = squareSize * 1.8f;
        float scale = iconTargetSize / static_cast<float>(std::max(texSize.x, texSize.y));
        iconSprite.setScale(scale, scale);
        // Center the icon in the square
        iconSprite.setPosition(
            square.getPosition().x + (squareSize - texSize.x * scale) / 2.f,
            square.getPosition().y + (squareSize - texSize.y * scale) / 2.f
        );
        window.draw(iconSprite);
    }

}
