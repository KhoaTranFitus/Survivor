#include "NoOverlapComponent.h"
#include "GameObject.h"

void NoOverlapComponent::update(float deltaTime) {
    if (!gameObjects) return;
    auto& myHitbox = owner->getHitbox();
    for (auto& obj : *gameObjects) {
        if (obj.get() == owner.get()) continue;
        if (obj->getTag() != "enemies") continue;

        auto& otherHitbox = obj->getHitbox();
        if (myHitbox.getGlobalBounds().intersects(otherHitbox.getGlobalBounds())) {
            // Đẩy owner ra khỏi obj (chỉ cần đơn giản: đẩy theo trục x/y)
            sf::Vector2f myPos = myHitbox.getPosition();
            sf::Vector2f otherPos = otherHitbox.getPosition();
            sf::Vector2f delta = myPos - otherPos;

            if (delta.x == 0 && delta.y == 0) delta.x = 1.f; // tránh chia cho 0

            float len = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            if (len == 0) len = 1.f;
            sf::Vector2f pushDir = delta / len;

            // Đẩy ra một khoảng nhỏ (có thể điều chỉnh)
            float pushAmount = 2.f;
            owner->move(pushDir * pushAmount);
        }
    }
}