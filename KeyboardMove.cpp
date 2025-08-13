#include "KeyboardMove.h"
#include <SFML/Window/Keyboard.hpp>
#include "GameManager.h"
#include "Player.h"

KeyboardMove::KeyboardMove(std::shared_ptr<GameObject> owner, float speed, std::string mode)
    : Component(owner),
    speed(speed),
    mode(mode)
{
        up = sf::Keyboard::W;
        down = sf::Keyboard::S;
        left = sf::Keyboard::A;
        right = sf::Keyboard::D;
}

sf::Vector2f KeyboardMove::getDirection() const
{
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(this->up))
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(this->down))
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(this->left))
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(this->right))
        direction.x += 1.f;

    return direction;
}

void KeyboardMove::update(float deltaTime)
{
    auto player = std::dynamic_pointer_cast<Player>(owner);
    if (player && !player->isControllable()) {
        // Nếu player không thể điều khiển (đã chết), bỏ qua xử lý input
        return;
    }

    if (!owner) return;

    // Truy cập và di chuyển hitbox của GameObject
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(this->up))
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(this->down))
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(this->left))
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(this->right))
        direction.x += 1.f;

    if (direction.x != 0.f || direction.y != 0.f) {
        // Normalize diagonal movement
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.f) {
            direction /= length;
        }
        // Move with consistent speed in all directions
        owner->move(direction * speed * deltaTime);
    }
}

