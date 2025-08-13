#include "Shield.h"
#include "Stat.h"
#include "GameObject.h"
#include "Assets.h" // Add this include

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
    // Increase bar size
    float barWidth = 180.f;   // was 120.f
    float barHeight = 28.f;   // was 16.f
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

    // Square background
    float squareSize = barHeight;
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
    // Make the square background more transparent (alpha = 80)
    square.setFillColor(sf::Color(50, 50, 180, 80));
    square.setOutlineColor(sf::Color::White);
    square.setOutlineThickness(2.f);
    square.setPosition(x - 38.f, y); // adjust for larger barHeight
    //window.draw(square);

    // Draw asset image inside square, larger and centered
    sf::Sprite shieldIconSprite;
    shieldIconSprite.setTexture(Assets::SHIELD_ITEM);
    sf::Vector2u shieldTexSize = Assets::SHIELD_ITEM.getSize();
    if (shieldTexSize.x > 0 && shieldTexSize.y > 0) {
        // Make icon larger (e.g. 1.8x the square size)
        float iconTargetSize = squareSize * 1.8f;
        float scale = iconTargetSize / static_cast<float>(std::max(shieldTexSize.x, shieldTexSize.y));
        shieldIconSprite.setScale(scale, scale);
        // Center the icon in the square
        shieldIconSprite.setPosition(
            square.getPosition().x + (squareSize - shieldTexSize.x * scale) / 2.f,
            square.getPosition().y + (squareSize - shieldTexSize.y * scale) / 2.f
        );
        window.draw(shieldIconSprite);
    }

}