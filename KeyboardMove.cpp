#include "KeyboardMove.h"
#include <SFML/Window/Keyboard.hpp>
//#include "CollideWithBounds.h"
#include "GameManager.h"

KeyboardMove::KeyboardMove(std::shared_ptr<GameObject> owner, float speed, std::string mode)
    : Component(owner),
    speed(speed),
    mode(mode)
{
    if (mode == "arrows")
    {
        up = sf::Keyboard::Up;
        down = sf::Keyboard::Down;
        left = sf::Keyboard::Left;
        right = sf::Keyboard::Right;
    }
    else
    {
        // Mặc định là WASD nếu mode không hợp lệ
        up = sf::Keyboard::W;
        down = sf::Keyboard::S;
        left = sf::Keyboard::A;
        right = sf::Keyboard::D;
    }
}

void KeyboardMove::update(float deltaTime)
{
    if (!owner) return;

    // Truy cập và di chuyển hitbox của GameObject
    sf::Vector2f movement(0.f, 0.f);

    auto stat = owner->getComponent<Stat>();
    float moveSpeed = stat ? stat->getSpeed() : speed;

    if (sf::Keyboard::isKeyPressed(this->up))
        movement.y -= moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(this->down))
        movement.y += moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(this->left))
        movement.x -= moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(this->right))
        movement.x += moveSpeed * deltaTime;

    
    this->owner->move(movement);
}

